#pragma once

#include <HazelPVR.hpp>

enum class Distributions
{
    RANDOM_UNIFORM,
    RANDOM_GAUSSIAN
};

struct Bound
{
        float left;
        float right;
        float top;
        float bottom;
};

enum class Direction
{
    X,
    Y
};

class Particle2D
{
    public:
        Particle2D() = default;
        ~Particle2D() = default;

    public:
        void Init(glm::vec2 size, const Bound& bound, Distributions distribution);

        glm::vec2 GetPosition() const { return m_Position; }
        void SetPosition(glm::vec2 pos) { m_Position = pos; }

        glm::vec2 GetVelocity() const { return m_Velocity; }
        void SetVelocity(glm::vec2 pos) { m_Velocity = pos; }

        glm::vec2 GetSize() const { return m_Size; }
        void SetSize(glm::vec2 size) { m_Size = size; }

        glm::vec4 GetColor() const { return m_Color; }
        void SetColor(glm::vec4 pos) { m_Color = pos; }

        bool HasFlipped(Direction direction) const
        {
            switch (direction)
            {
            case Direction::X:
                return m_Flipped_x;
            case Direction::Y:
                return m_Flipped_y;
            }
        }
        void HasFlipped(Direction direction, bool state)
        {
            switch (direction)
            {
            case Direction::X:
                m_Flipped_x = state;
                break;
            case Direction::Y:
                m_Flipped_y = state;
                break;
            }
        }

    private:
        glm::vec2 m_Size;
        glm::vec4 m_Color;
        glm::vec2 m_Position;
        glm::vec2 m_Velocity;

        bool m_Flipped_x = false;
        bool m_Flipped_y = false;
};
