#ifndef TOOL_H
#define TOOL_H

#include <QByteArray>
#include <QString>

class Tool
{
public:
    Tool(int id,
         const QString &name,
         int descId,
         const QString &desc,
         const QString &len,
         const QString &outDia,
         const QString &inDia,
         const QByteArray &img,
         int prodId,
         const QString &prodName);

    static Tool create(int id,
                       const QString &name,
                       int descId,
                       const QString &desc,
                       const QString &len,
                       const QString &outDia,
                       const QString &inDia,
                       const QByteArray &img,
                       int prodId,
                       const QString &prodName)
    {
        return Tool(id, name, descId, desc, len, outDia, inDia, img, prodId, prodName);
    }

    int getToolId() const;
    QString getToolName() const;
    int getToolDescriptionId() const;
    QString getDescription() const;
    QString getLength() const;
    QString getOuterDiameter() const;
    QString getInnerDiameter() const;
    QByteArray getImage() const;
    int getProduserId() const;
    QString getProduserName() const;

    void setToolId(int id);
    void setToolName(const QString &name);
    void setToolDescriptionId(int id);
    void setDescription(const QString &desc);
    void setLength(const QString &len);
    void setOuterDiameter(const QString &outDia);
    void setInnerDiameter(const QString &inDia);
    void setImage(const QByteArray &img);
    void setProduserId(int id);
    void setProduserName(const QString &name);

    bool operator==(const Tool &other) const;

private:
    int toolId;
    QString toolName;
    int toolDescriptionId;
    QString description;
    QString length;
    QString outerDiameter;
    QString innerDiameter;
    QByteArray image;
    int produserId;
    QString produserName;
};

#endif // TOOL_H
