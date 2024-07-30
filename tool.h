#ifndef TOOL_H
#define TOOL_H

#include <QByteArray>
#include <QString>

class Tool
{
public:
    static Tool *create(int toolId,
                        int produserId,
                        int toolDescriptionId,
                        const QString &toolName,
                        const QString &produserName,
                        const QString &description,
                        const QString &length,
                        const QString &outerDiameter,
                        const QString &innerDiameter,
                        const QByteArray &image);

    Tool(int toolId,
         int produserId,
         int toolDescriptionId,
         const QString &toolName,
         const QString &produserName,
         const QString &description,
         const QString &length,
         const QString &outerDiameter,
         const QString &innerDiameter,
         const QByteArray &image);

    // Getters
    int getToolId() const;
    int getProduserId() const;
    int getToolDescriptionId() const;
    QString getToolName() const;
    QString getProduserName() const;
    QString getDescription() const;
    QString getLength() const;
    QString getOuterDiameter() const;
    QString getInnerDiameter() const;
    QByteArray getImage() const;

    // Setters
    void setToolId(int newToolId);
    void setProduserId(int newProduserId);
    void setToolDescriptionId(int newToolDescriptionId);
    void setToolName(const QString &newToolName);
    void setProduserName(const QString &newProduserName);
    void setDescription(const QString &newDescription);
    void setLength(const QString &newLength);
    void setOuterDiameter(const QString &newOuterDiameter);
    void setInnerDiameter(const QString &newInnerDiameter);
    void setImage(const QByteArray &newImage);

    // Comparison operator
    bool operator==(const Tool &other) const;

private:
    int toolId;
    int produserId;
    int toolDescriptionId;
    QString toolName;
    QString produserName;
    QString description;
    QString length;
    QString outerDiameter;
    QString innerDiameter;
    QByteArray image;
};

#endif // TOOL_H
