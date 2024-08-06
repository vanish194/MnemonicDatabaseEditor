#include "tool.h"

// Default constructor
Tool::Tool()
    : toolId(0)
    , toolDescriptionId(0)
    , produserId(0)
{}

Tool::Tool(int id,
           const QString &name,
           int descId,
           const QString &desc,
           const QString &len,
           const QString &outDia,
           const QString &inDia,
           const QByteArray &img,
           int prodId,
           const QString &prodName)
    : toolId(id)
    , toolName(name)
    , toolDescriptionId(descId)
    , description(desc)
    , length(len)
    , outerDiameter(outDia)
    , innerDiameter(inDia)
    , image(img)
    , produserId(prodId)
    , produserName(prodName)
{}

int Tool::getToolId() const
{
    return toolId;
}
QString Tool::getToolName() const
{
    return toolName;
}
int Tool::getToolDescriptionId() const
{
    return toolDescriptionId;
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
int Tool::getProduserId() const
{
    return produserId;
}
QString Tool::getProduserName() const
{
    return produserName;
}

void Tool::setToolId(int id)
{
    toolId = id;
}
void Tool::setToolName(const QString &name)
{
    toolName = name;
}
void Tool::setToolDescriptionId(int id)
{
    toolDescriptionId = id;
}
void Tool::setDescription(const QString &desc)
{
    description = desc;
}
void Tool::setLength(const QString &len)
{
    length = len;
}
void Tool::setOuterDiameter(const QString &outDia)
{
    outerDiameter = outDia;
}
void Tool::setInnerDiameter(const QString &inDia)
{
    innerDiameter = inDia;
}
void Tool::setImage(const QByteArray &img)
{
    image = img;
}
void Tool::setProduserId(int id)
{
    produserId = id;
}
void Tool::setProduserName(const QString &name)
{
    produserName = name;
}

bool Tool::operator==(const Tool &other) const
{
    return toolId == other.toolId && toolName == other.toolName
           && toolDescriptionId == other.toolDescriptionId && description == other.description
           && length == other.length && outerDiameter == other.outerDiameter
           && innerDiameter == other.innerDiameter && image == other.image
           && produserId == other.produserId && produserName == other.produserName;
}
