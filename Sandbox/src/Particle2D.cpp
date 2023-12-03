#include "Particle2D.hpp"

#include <random>

void Particle2D::Init(glm::vec2 size, const Bound& bound, Distributions distribution)
{
    std::random_device random_device;
    std::mt19937 generate(random_device());
    std::uniform_real_distribution<float> UPosHor(bound.left, bound.right);
    std::uniform_real_distribution<float> UPosVer(bound.bottom, bound.top);
    std::normal_distribution<float> NPosHor(bound.left, bound.right);
    std::normal_distribution<float> NPosVer(bound.bottom, bound.top);
    std::uniform_real_distribution<float> UVelocity(-2.0f, 2.0f);
    std::normal_distribution<float> NVelocity(-2.0f, 2.0f);
    std::uniform_real_distribution<float> Color(0.0f, 1.0f);

    m_Size = size;
    m_Color = {Color(generate), Color(generate), Color(generate), 1.0f};

    switch (distribution)
    {
    case Distributions::RANDOM_UNIFORM:
        m_Position = {UPosHor(generate), UPosVer(generate)};
        m_Velocity = {UVelocity(generate), UVelocity(generate)};
        break;
    case Distributions::RANDOM_GAUSSIAN:
        m_Position = {NPosHor(generate), NPosVer(generate)};
        m_Velocity = {NVelocity(generate), NVelocity(generate)};
        break;
    default:
        break;
    }
}