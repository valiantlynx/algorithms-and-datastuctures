#include "Entity.hpp"

Entity::Entity()
    : mPosition(0.f, 0.f)
    , mVelocity(0.f, 0.f)
    , mActive(true)
{
}

void Entity::setPosition(float x, float y) {
    mPosition.x = x;
    mPosition.y = y;
    mSprite.setPosition(mPosition);
}

sf::Vector2f Entity::getPosition() const {
    return mPosition;
}

sf::FloatRect Entity::getBounds() const {
    return mSprite.getGlobalBounds();
}

bool Entity::intersects(const Entity& other) const {
    return getBounds().intersects(other.getBounds());
}
