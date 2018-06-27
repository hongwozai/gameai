#ifndef BASEGAMEENTITY_H
#define BASEGAMEENTITY_H

struct Telegram;
class BaseGameEntity
{
public:

    BaseGameEntity(int id) { setID(id); }

    void setID(int id);

    int  getID() const { return this->id; }

public:

    virtual ~BaseGameEntity() {}

    virtual void update() = 0;

    virtual bool handleMessage(Telegram &telegram) = 0;

private:

    static int nextValidID;

private:

    int id;
};

inline void BaseGameEntity::setID(int id)
{
    this->id = id;
    nextValidID++;
}

#endif /* BASEGAMEENTITY_H */
