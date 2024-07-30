#include "tool.h"

Tool *Tool::create(int toolId,
                   int produserId,
                   int toolDescriptionId,
                   const QString &toolName,
                   const QString &produserName,
                   const QString &description,
                   const QString &length,
                   const QString &outerDiameter,
                   const QString &innerDiameter,
                   const QByteArray &image)
{
    return new Tool(toolId,
                    produserId,
                    toolDescriptionId,
                    toolName,
                    produserName,
                    description,
                    length,
                    outerDiameter,
                    innerDiameter,
                    image);
}

Tool::Tool(int toolId,
           int produserId,
           int toolDescriptionId,
           const QString &toolName,
           const QString &produserName,
           const QString &description,
           const QString &length,
           const QString &outerDiameter,
           const QString &innerDiameter,
           const QByteArray &image)
    : toolId(toolId)
    , produserId(produserId)
    , toolDescriptionId(toolDescriptionId)
    , toolName(toolName)
    , produserName(produserName)
    , description(description)
    , length(length)
    , outerDiameter(outerDiameter)
    , innerDiameter(innerDiameter)
    , image(image)
{}

// Getters
int Tool::getToolId() const
{
    return toolId;
}
int Tool::getProduserId() const
{
    return produserId;
}
int Tool::getToolDescriptionId() const
{
    return toolDescriptionId;
}
QString Tool::getToolName() const
{
    return toolName;
}
QString Tool::getProduserName() const
{
    return produserName;
}
QString Tool::getDescription() const
{
    return description;
}
QString Tool::getLength() const
{
    return length;
}
QString Tool::getOuterDiameter() const
{
    return outerDiameter;
}
QString Tool::getInnerDiameter() const
{
    return innerDiameter;
}
QByteArray Tool::getImage() const
{
    return image;
}

// Setters
void Tool::setToolId(int newToolId)
{
    toolId = newToolId;
}
void Tool::setProduserId(int newProduserId)
{
    produserId = newProduserId;
}
void Tool::setToolDescriptionId(int newToolDescriptionId)
{
    toolDescriptionId = newToolDescriptionId;
}
void Tool::setToolName(const QString &newToolName)
{
    toolName = newToolName;
}
void Tool::setProduserName(const QString &newProduserName)
{
    produserName = newProduserName;
}
void Tool::setDescription(const QString &newDescription)
{
    description = newDescription;
}
void Tool::setLength(const QString &newLength)
{
    length = newLength;
}
void Tool::setOuterDiameter(const QString &newOuterDiameter)
{
    outerDiameter = newOuterDiameter;
}
void Tool::setInnerDiameter(const QString &newInnerDiameter)
{
    innerDiameter = newInnerDiameter;
}
void Tool::setImage(const QByteArray &newImage)
{
    image = newImage;
}

// Comparison operator
bool Tool::operator==(const Tool &other) const
{
    return toolId == other.toolId && produserId == other.produserId
           && toolDescriptionId == other.toolDescriptionId && toolName == other.toolName
           && produserName == other.produserName && description == other.description
           && length == other.length && outerDiameter == other.outerDiameter
           && innerDiameter == other.innerDiameter && image == other.image;
}
