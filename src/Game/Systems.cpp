#include "Headers/Systems.hpp"

#include <SFML/Graphics.hpp>

NacreCoordinator& systemsNC = NacreCoordinator::getInstance();

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void Start::setText(sf::Font& font)
{
    auto& texts = systemsNC.getComponentArray<Component::Text>();

    for (auto& [entity, text] : texts->getAll())
    {
        text.box.value().setString(text.string);
        text.box.value().setCharacterSize(text.size);
        text.box.value().setFillColor(text.color);
    }
}
void Start::setTextOrigin()
{
    auto& texts = systemsNC.getComponentArray<Component::Text>();
    auto& transforms = systemsNC.getComponentArray<Component::Transform>();

    double offsetX;
    double offsetY;

    for (auto& [entity, text] : texts->getAll())
    {
        if (!transforms->hasData(entity))
        {
            continue;
        }

        Component::Transform& transform = transforms->getData(entity);

        switch (text.format)
        {
        case Enum::TextFormat::TOP:
            offsetX = text.box.value().getLocalBounds().size.x / 2;
            offsetY = text.box.value().getLocalBounds().size.y;
            break;
        case Enum::TextFormat::BOTTOM:
            offsetX = text.box.value().getLocalBounds().size.x / 2;
            offsetY = text.box.value().getLocalBounds().size.y / 2;
            break;
        case Enum::TextFormat::MIDDLE:
        default:
            offsetX = text.box.value().getLocalBounds().size.x / 2;
            offsetY = (text.box.value().getLocalBounds().size.y / 2) + (text.box.value().getLocalBounds().size.y / 4);
            break;
        }

        text.box.value().setOrigin
        (
            sf::Vector2f
            {
                static_cast<float>(offsetX),
                static_cast<float>(offsetY)
            }
        );
    }
}
void Start::setSpriteOrigin()
{
    auto& originArray = systemsNC.getComponentArray<Component::Origin>();
    auto& spriteArray = systemsNC.getComponentArray<Component::Sprite>();


    for (auto& [entity, sprite] : spriteArray->getAll())
    {
        if (!originArray->hasData(entity))
        {
            continue;
        }

        Component::Origin& origin = originArray->getData(entity);

        sprite.body->setOrigin
        (
            sf::Vector2f
            {
                static_cast<float>(origin.offsetX / sprite.body->getScale().x),
                static_cast<float>(origin.offsetY / sprite.body->getScale().y)
            }
        );
    }
}
void Start::loadTextures(Entity loadedTextures)
{
    auto& texturesContainerArray = systemsNC.getComponentArray<Component::TexturesContainer>();

    if (!texturesContainerArray->hasData(loadedTextures))
    {
        return;
    }

    Component::TexturesContainer& container = texturesContainerArray->getData(loadedTextures);

    container.map.emplace(Enum::Texture::TEXTURE_PLACEHOLDER, sf::Texture(SPRITES_PATH "placeholder_texture.jpeg"));
}
void Start::loadSprites(Entity loadedTextures)
{
    auto& spriteArray = systemsNC.getComponentArray<Component::Sprite>();
    auto& transformArray = systemsNC.getComponentArray<Component::Transform>();
    auto& textureArray = systemsNC.getComponentArray<Component::Texture>();
    auto& texturesContainerArray = systemsNC.getComponentArray<Component::TexturesContainer>();

    if (!texturesContainerArray->hasData(loadedTextures))
    {
        return;
    }

    Component::TexturesContainer& container = texturesContainerArray->getData(loadedTextures);

    for (auto& [entity, sprite] : spriteArray->getAll())
    {
        if
            (
                !transformArray->hasData(entity) ||
                !textureArray->hasData(entity)
                )
        {
            continue;
        }

        Component::Texture& texture = textureArray->getData(entity);
        Component::Transform& transform = transformArray->getData(entity);

        sprite.body.emplace(container.map[texture.data]);
        sprite.body->setScale
        (
            sf::Vector2f
            {
                static_cast<float>(transform.width / sprite.body->getGlobalBounds().size.x),
                static_cast<float>(transform.height / sprite.body->getGlobalBounds().size.y)
            }
        );
    }
}
void Start::setColor()
{
    auto& colorArray = systemsNC.getComponentArray<Component::Color>();
    auto& spriteArray = systemsNC.getComponentArray<Component::Sprite>();

    for (auto& [entity, color] : colorArray->getAll())
    {
        if (!spriteArray->hasData(entity))
        {
            continue;
        }

        Component::Color& colorObj = colorArray->getData(entity);
        Component::Sprite& spriteObj = spriteArray->getData(entity);

        spriteObj.body->setColor(colorObj.col);
    }
}

// -------------------------------------------------------
// control systems
// -------------------------------------------------------
const double DEFAULT_SCALE_X = 1.0f;
const double DEFAULT_SCALE_Y = 1.0f;

const double HOVER_SCALE_X = 1.1f;
const double HOVER_SCALE_Y = 1.1f;

const double CLICKED_SCALE_X = 0.9f;
const double CLICKED_SCALE_Y = 0.9f;

void Control::buttonClicks
(
    const sf::Vector2i mouseVector,
    const DeltaTime dt
)
{
    auto& buttonArray = systemsNC.getComponentArray<Component::Button>();
    auto& originArray = systemsNC.getComponentArray<Component::Origin>();
    auto& transformArray = systemsNC.getComponentArray<Component::Transform>();
    auto& positionArray = systemsNC.getComponentArray<Component::Position>();

    for (auto& [entity, button] : buttonArray->getAll())
    {
        if (!button.enabled ||
            !originArray->hasData(entity) ||
            !positionArray->hasData(entity) ||
            !transformArray->hasData(entity))
        {
            continue;
        }

        // buttonArray must have a shape, origin, and text
        ////std::cout << "button.top: " << button.top << "\n";
        ////std::cout << "button.left: " << button.left << "\n";
        const Component::Origin& origin = originArray->getData(entity);
        const Component::Transform& transform = transformArray->getData(entity);
        const Component::Position& position = positionArray->getData(entity);

        if
            (
                mouseVector.x > position.x - origin.offsetX &&
                mouseVector.x < position.x + transform.width - origin.offsetX &&
                mouseVector.y > position.y - origin.offsetY &&
                mouseVector.y < position.y + transform.height - origin.offsetY
                )
        {
            button.clicked = true;
            button.clickedTimer = button.clickedDuration;
        }
    }
}
void Control::doPlayerControl
(
    const Entity player,
    const DeltaTime dt
)
{
    auto& velocities = systemsNC.getComponentArray<Component::Velocity>();
    auto& speeds = systemsNC.getComponentArray<Component::Speed>();
    auto& playerControllers = systemsNC.getComponentArray<Component::PlayerController>();

    if (!velocities->hasData(player) ||
        !speeds->hasData(player) ||
        !playerControllers->hasData(player))
    {
        return;
    }

    const Component::PlayerController playerController = playerControllers->getData(player);
    const Component::Speed speed = speeds->getData(player);
    Component::Velocity& velocity = velocities->getData(player);

    if (!playerController.enabled)
    {
        return;
    }

    double newSpeedX = 0.f;
    double newSpeedY = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        newSpeedY = -speed.y;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        newSpeedY = speed.y;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        newSpeedX = -speed.x;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        newSpeedX = speed.x;
    }

    // applies the speed (even if there aren't any changes)
    velocity.x += (newSpeedX * dt);
    velocity.y += (newSpeedY * dt);

    if (velocity.x > velocity.maxX)
    {
        velocity.x = velocity.maxX;
    }
    else if (velocity.x < velocity.minX)
    {
        velocity.x = velocity.minX;
    }

    if (velocity.y > velocity.maxY)
    {
        velocity.y = velocity.maxY;
    }
    else if (velocity.y < velocity.minY)
    {
        velocity.y = velocity.minY;
    }

}

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
void Update::doButtons
(
    const sf::Vector2i mouseVector,
    const DeltaTime dt
) {
    auto& spriteArray = systemsNC.getComponentArray<Component::Sprite>();
    auto& buttonArray = systemsNC.getComponentArray<Component::Button>();
    auto& originArray = systemsNC.getComponentArray<Component::Origin>();
    auto& textArray = systemsNC.getComponentArray<Component::Text>();
    auto& nextSceneArray = systemsNC.getComponentArray<Component::NextScene>();
    auto& transformArray = systemsNC.getComponentArray<Component::Transform>();
    auto& positionArray = systemsNC.getComponentArray<Component::Position>();

    for (auto& [entity, button] : buttonArray->getAll())
    {
        if (!button.enabled)
        {
            continue;
        }

        // buttonArray must have a shape, origin, and text
        if (!originArray->hasData(entity) ||
            !positionArray->hasData(entity) ||
            !spriteArray->hasData(entity))
        {
            continue;
        }

        ////std::cout << "button.top: " << button.top << "\n";
        ////std::cout << "button.left: " << button.left << "\n";
        Component::Origin& origin = originArray->getData(entity);
        Component::Transform& transform = transformArray->getData(entity);
        Component::Position& position = positionArray->getData(entity);
        Component::Sprite& sprite = spriteArray->getData(entity);

        if (button.clickedTimer <= 0)
        {
            sprite.body->setScale
            (
                sf::Vector2f
                (
                    DEFAULT_SCALE_X * (transform.width / sprite.body->getTexture().getSize().x),
                    DEFAULT_SCALE_Y * (transform.height / sprite.body->getTexture().getSize().y)
                )
            );

            if (textArray->hasData(entity))
            {
                Component::Text& text = textArray->getData(entity);
                text.box->setScale
                (
                    sf::Vector2f
                    (
                        DEFAULT_SCALE_X,
                        DEFAULT_SCALE_Y
                    )
                );
            }
        }
        else
        {
            button.clickedTimer -= dt;
            if (button.clickedTimer <= 0)
            {
                button.clicked = true;

                if (nextSceneArray->hasData(entity))
                {
                    ////std::cout << "starting next scene." << "\n";
                    Component::NextScene& nextScene = nextSceneArray->getData(entity);
                    nextScene.active = true;
                }
            }
        }

        // button hovering
        if
            (
                mouseVector.x > position.x - origin.offsetX &&
                mouseVector.x < position.x + transform.width - origin.offsetX &&
                mouseVector.y > position.y - origin.offsetY &&
                mouseVector.y < position.y + transform.height - origin.offsetY &&
                button.clickedTimer <= 0
                )
        {
            sprite.body->setScale
            (
                sf::Vector2f
                (
                    HOVER_SCALE_X * (transform.width / sprite.body->getTexture().getSize().x),
                    HOVER_SCALE_Y * (transform.height / sprite.body->getTexture().getSize().y)
                )
            );

            if (textArray->hasData(entity))
            {
                Component::Text& text = textArray->getData(entity);
                text.box->setScale
                (
                    sf::Vector2f
                    (
                        HOVER_SCALE_X,
                        HOVER_SCALE_Y
                    )
                );
            }
        }

        // button clicking
        if (button.clickedTimer > 0)
        {
            sprite.body->setScale
            (
                sf::Vector2f
                (
                    CLICKED_SCALE_X * (transform.width / sprite.body->getTexture().getSize().x),
                    CLICKED_SCALE_Y * (transform.height / sprite.body->getTexture().getSize().y)
                )
            );

            if (textArray->hasData(entity))
            {
                Component::Text& text = textArray->getData(entity);
                text.box->setScale
                (
                    sf::Vector2f
                    (
                        CLICKED_SCALE_X,
                        CLICKED_SCALE_Y
                    )
                );
            }
        }
    }
}
void Update::doNextScene
(
    sf::RenderWindow& window,
    sf::Font& font
)
{
    auto& nextScenes = systemsNC.getComponentArray<Component::NextScene>();

    bool playNext = false;
    Scene playNextScene;

    for (auto& [entity, nextScene] : nextScenes->getAll())
    {
        // buttons must have a shape, origin, and text
        if (nextScene.active)
        {
            //std::cout << "active: " << nextScene.next << "\n";
            playNext = true;
            playNextScene = nextScene.next;
            break;
        }
    }

    if (playNext)
    {
        systemsNC.destroyAll();
        playScene
        (
            window,
            playNextScene,
            font
        );
        window.close();
    }
}
void Update::move(const DeltaTime dt)
{
    auto& velocities = systemsNC.getComponentArray<Component::Velocity>();
    auto& positions = systemsNC.getComponentArray<Component::Position>();

    for (auto& [entity, velocity] : velocities->getAll())
    {
        if (!positions->hasData(entity))
        {
            continue;
        }

        Component::Position& pos = positions->getData(entity);
        pos.x += (velocity.x * dt);
        pos.y += (velocity.y * dt);
    }
}
void Update::drag(const DeltaTime dt)
{
    auto& velocities = systemsNC.getComponentArray<Component::Velocity>();
    auto& drags = systemsNC.getComponentArray<Component::Drag>();

    for (auto& [entity, velocity] : velocities->getAll())
    {
        if (!drags->hasData(entity))
        {
            continue;
        }

        Component::Drag drag = drags->getData(entity);

        // can't be exactly 0.f because it will drift aimlessly
        velocity.x = velocity.x < -0.1f ? velocity.x + (drag.x * dt) :
            velocity.x > 0.1f ? velocity.x - (drag.x * dt) : 0.f;
        velocity.y = velocity.y < -0.1f ? velocity.y + (drag.y * dt) :
            velocity.y > 0.1f ? velocity.y - (drag.y * dt) : 0.f;
    }
}

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void Render::doZIndex(std::queue<Entity>& renderQueue)
{
    auto& zIndexes = systemsNC.getComponentArray<Component::ZIndex>();

    std::vector<std::pair<int, Entity>> renderVector;
    for (auto& [entity, zIndex] : zIndexes->getAll())
    {
        if (zIndex.visible) renderVector.emplace_back(zIndex.index, entity);
    }
    std::sort(renderVector.begin(), renderVector.end());

    for (auto& [zIndex, entity] : renderVector)
    {
        renderQueue.push(entity);
    }
}
void Render::render
(
    sf::RenderWindow& window,
    std::queue<Entity>& renderQueue
)
{
    auto& spriteArray = systemsNC.getComponentArray<Component::Sprite>();
    auto& positionArray = systemsNC.getComponentArray<Component::Position>();
    auto& textArray = systemsNC.getComponentArray<Component::Text>();

    while (!renderQueue.empty())
    {
        Entity& popped = renderQueue.front();
        ////std::cout << "popped: " << popped << "\n";

        if
            (
                !positionArray->hasData(popped)
                )
        {
            // this means the entity does not have a position component
            continue;
        }

        Component::Position& pos = positionArray->getData(popped);

        if (spriteArray->hasData(popped))
        {
            Component::Sprite& sprite = spriteArray->getData(popped);

            sprite.body->setPosition
            (
                sf::Vector2f
                {
                    static_cast<float>(pos.x),
                    static_cast<float>(pos.y)
                }
            );
            window.draw(sprite.body.value());
        }

        if (textArray->hasData(popped))
        {
            Component::Text& text = textArray->getData(popped);

            text.box->setPosition
            (
                sf::Vector2f
                {
                    static_cast<float>(pos.x),
                    static_cast<float>(pos.y)
                }
            );
            window.draw(text.box.value());
        }

        renderQueue.pop();
    }
}