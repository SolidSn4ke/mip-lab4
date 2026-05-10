#include "trace.h"
#include "intersection.h"
#include "sampling.h"
#include <algorithm>
#include <limits>

Color trace(const Ray& ray, const Scene& scene, int depth) {
    // 1. Russian Roulette for path termination
    float rrProb = 0.9f; // Probability of continuing the path
    if (depth > 0) {
        if (Sampling::randomFloat() > rrProb) {
            return Color(0.0f, 0.0f, 0.0f);
        }
    }

    float closestT = std::numeric_limits<float>::max();
    bool hitSomething = false;
    HitInfo bestHit;
    const Triangle* hitTriangle = nullptr;

    // Find nearest intersection
    for (const auto& tri : scene.triangles) {
        HitInfo hit;
        if (intersectTriangle(ray, tri, hit)) {
            if (hit.t < closestT) {
                closestT = hit.t;
                bestHit = hit;
                hitSomething = true;
                hitTriangle = &tri;
            }
        }
    }

    if (!hitSomething) {
        return Color(0.0f, 0.0f, 0.0f); // Background
    }

    // Ensure normal faces the ray
    if (bestHit.normal.dot(ray.direction) > 0) {
        bestHit.normal = bestHit.normal * -1.0f;
    }

    Vector hitPos = ray.origin + ray.direction * closestT;
    const Material& mat = hitTriangle->material;

    // 2. Direct lighting from extended sources (Next Event Estimation)
    Color directLighting(0.0f, 0.0f, 0.0f);
    if (!scene.lights.empty()) {
        const auto& light = scene.lights[rand() % scene.lights.size()];
        Vector lightPoint = light.samplePoint();
        Vector lightVec = lightPoint - hitPos;
        float distSq = lightVec.length() * lightVec.length();
        Vector lightDir = lightVec.normalize();

        // Shadow ray to check visibility
        bool visible = true;
        float shadowT = 0.001f; // Bias
        Ray shadowRay(hitPos + bestHit.normal * shadowT, lightDir);
        for (const auto& tri : scene.triangles) {
            HitInfo sh;
            if (intersectTriangle(shadowRay, tri, sh) && sh.t < std::sqrt(distSq)) {
                visible = false;
                break;
            }
        }

        if (visible) {
            float cosTheta = std::max(0.0f, bestHit.normal.dot(lightDir));
            float cosPhi = std::max(0.0f, light.getNormal().dot(lightDir * -1.0f));
            float falloff = 1.0f / (distSq + 1.0f);
            directLighting = light.color * cosTheta * cosPhi * falloff * light.getArea();
        }
    }

    // 3. Indirect lighting / Material interaction
    Color indirectLighting(0.0f, 0.0f, 0.0f);
    float sample = Sampling::randomFloat();

    if (sample < mat.specularCoeff) {
        // Mirror reflection
        Vector reflectDir = ray.direction - bestHit.normal * 2.0f * ray.direction.dot(bestHit.normal);
        Ray nextRay(hitPos + bestHit.normal * 0.001f, reflectDir.normalize());
        indirectLighting = trace(nextRay, scene, depth + 1);
    } else {
        // Diffuse reflection (Lambertian)
        Vector nextDir = Sampling::sampleHemisphere(bestHit.normal);
        Ray nextRay(hitPos + bestHit.normal * 0.001f, nextDir);
        indirectLighting = trace(nextRay, scene, depth + 1);
    }

    // Energy conservation for Russian Roulette
    float rrWeight = (depth == 0) ? 1.0f : (1.0f / rrProb);

    return (directLighting + indirectLighting) * mat.diffuseColor * rrWeight;
}
