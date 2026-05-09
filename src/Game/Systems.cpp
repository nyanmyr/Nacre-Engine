#include "Headers/Systems.hpp"

#include <SFML/Graphics.hpp>

NacreCoordinator& systemsNC = NacreCoordinator::getInstance();

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void SetTextSystem(sf::Font font)
{
    auto& texts = systemsNC.getComponentArray<CText>();

    for (auto& [entity, text] : texts->getAll())
    {
        text.box.setString(text.string);
        text.box.setCharacterSize(text.size);
        text.box.setFillColor(text.color);
    }
}
void SetTextOriginSystem()
{
    auto& texts = systemsNC.getComponentArray<CText>();
    auto& transforms = systemsNC.getComponentArray<CTransform>();

    float offsetX;
    float offsetY;

    for (auto& [entity, text] : texts->getAll())
    {
        if (!transforms->hasData(entity))
        {
            continue;
        }

        CTransform& transform = transforms->getData(entity);

        switch (text.format)
        {
        case TOP:
            offsetX = text.box.getLocalBounds().size.x / 2;
            offsetY = text.box.getLocalBounds().size.y;
            break;
        case BOTTOM:
            offsetX = text.box.getLocalBounds().size.x / 2;
            offsetY = text.box.getLocalBounds().size.y / 2;
            break;
        case MIDDLE:
        default:
            offsetX = text.box.getLocalBounds().size.x / 2;
            offsetY = (text.box.getLocalBounds().size.y / 2) + (text.box.getLocalBounds().size.y / 4);
            break;
        }

        text.box.setOrigin
        (
            {
                offsetX,
                offsetY
            }
        );
    }
}
void SetShapeOriginSystem()
{
    auto& origins = systemsNC.getComponentArray<COrigin>();
    auto& shapes = systemsNC.getComponentArray<CShape>();

    for (auto& [entity, shape] : shapes->getAll())
    {
        if (!origins->hasData(entity))
        {
            continue;
        }

        COrigin& origin = origins->getData(entity);
        shape.rect.setOrigin
        (
            {
                origin.offsetX,
                origin.offsetY
            }
        );
    }
}

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
const float DEFAULT_SCALE_X = 1.0f;
const float DEFAULT_SCALE_Y = 1.0f;

const float HOVER_SCALE_X = 1.1f;
const float HOVER_SCALE_Y = 1.1f;

const float CLICKED_SCALE_X = 0.9f;
const float CLICKED_SCALE_Y = 0.9f;

void ButtonClickedSystem(sf::Vector2i& mouseVector, bool& buttonClicked, DeltaTime dt)
{
    //auto& shapes = systemsNC.getComponentArray<CShape>();
    auto& shapes = systemsNC.getComponentArray<CShape>();
    auto& buttons = systemsNC.getComponentArray<CButton>();
    auto& origins = systemsNC.getComponentArray<COrigin>();
    auto& texts = systemsNC.getComponentArray<CText>();
    auto& nextScenes = systemsNC.getComponentArray<CNextScene>();
    auto& transforms = systemsNC.getComponentArray<CTransform>();
    auto& positions = systemsNC.getComponentArray<CPosition>();

    for (auto& [entity, button] : buttons->getAll())
    {
        if (!button.enabled)
        {
            continue;
        }

        // buttons must have a shape, origin, and text
        if (origins->hasData(entity) &&
            texts->hasData(entity) &&
            positions->hasData(entity) &&
            shapes->hasData(entity))
        {
            //std::cout << "button.top: " << button.top << "\n";
            //std::cout << "button.left: " << button.left << "\n";
            COrigin& origin = origins->getData(entity);
            CText& text = texts->getData(entity);
            CTransform& transform = transforms->getData(entity);
            CPosition& position = positions->getData(entity);
            CShape& shape = shapes->getData(entity);

            button.clicked = false; // reset

            if (button.clickedTimer <= 0)
            {
                shape.rect.setScale
                (
                    sf::Vector2f
                    (
                        DEFAULT_SCALE_X,
                        DEFAULT_SCALE_Y
                    )
                );
                text.box.setScale
                (
                    sf::Vector2f
                    (
                        DEFAULT_SCALE_X,
                        DEFAULT_SCALE_Y
                    )
                );
            }
            else
            {
                button.clickedTimer -= dt;

                if (button.clickedTimer <= 0)
                {
                    button.clicked = true;

                    if (nextScenes->hasData(entity))
                    {
                        //std::cout << "starting next scene." << "\n";
                        CNextScene& nextScene = nextScenes->getData(entity);
                        nextScene.active = true;
                    }
                }
            }

            // button hovering
            if (mouseVector.x > position.x - origin.offsetX &&
                mouseVector.x < position.x + transform.width - origin.offsetX &&
                mouseVector.y > position.y - origin.offsetY &&
                mouseVector.y < position.y + transform.height - origin.offsetY &&
                button.clickedTimer <= 0)
            {
                shape.rect.setScale
                (
                    sf::Vector2f
                    (
                        HOVER_SCALE_X,
                        HOVER_SCALE_Y
                    )
                );
                text.box.setScale
                (
                    sf::Vector2f
                    (
                        HOVER_SCALE_X,
                        HOVER_SCALE_Y
                    )
                );

                if (buttonClicked)
                {
                    button.clickedTimer = button.clickedDuration;
                }
            }

            // button clicking
            if (button.clickedTimer > 0)
            {
                shape.rect.setScale
                (
                    sf::Vector2f
                    (
                        CLICKED_SCALE_X,
                        CLICKED_SCALE_Y
                    )
                );
                text.box.setScale
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
void NextSceneSystem(sf::RenderWindow& window, sf::Font& font)
{
    auto& nextScenes = systemsNC.getComponentArray<CNextScene>();

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
        playScene(window, playNextScene, font);
        window.close();
    }
}

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void ZIndexSystem(std::queue<Entity>& renderQueue)
{
    auto& zIndexes = systemsNC.getComponentArray<CZIndex>();

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
void RenderSystem(sf::RenderWindow& window, std::queue<Entity>& renderQueue)
{
    auto& shapes = systemsNC.getComponentArray<CShape>();
    auto& positions = systemsNC.getComponentArray<CPosition>();
    auto& texts = systemsNC.getComponentArray<CText>();
    auto& buttons = systemsNC.getComponentArray<CButton>();
    auto& origins = systemsNC.getComponentArray<COrigin>();

    while (!renderQueue.empty())
    {
        Entity& popped = renderQueue.front();
        //std::cout << "popped: " << popped << "\n";

        if (!positions->hasData(popped))
        {
            // this means the entity does not have a position component
            continue;
        }

        CPosition& pos = positions->getData(popped);
        COrigin& origin = origins->getData(popped);

        if (shapes->hasData(popped))
        {
            CShape& shape = shapes->getData(popped);

            shape.rect.setPosition
            (
                {
                    pos.x,
                    pos.y
                }
            );
            window.draw(shape.rect);
        }

        if (texts->hasData(popped))
        {
            CText& text = texts->getData(popped);

            text.box.setPosition
            (
                {
                    pos.x,
                    pos.y
                }
            );
            window.draw(text.box);
        }

        renderQueue.pop();
    }
}