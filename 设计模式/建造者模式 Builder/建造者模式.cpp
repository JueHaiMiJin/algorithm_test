// 建造者模式用于创建过程稳定，但配置多变的对象。在《设计模式》一书中的定义是：将一个复杂的构建与其表示相分离，
// 使得同样的构建过程可以创建不同的表示。

// 经典的“建造者 -指挥者”模式现在已经不太常用了，现在建造者模式主要用来通过链式调用生成不同的配置。比如我们要制作一杯珍珠奶茶。
// 它的制作过程是稳定的，除了必须要知道奶茶的种类和规格外，是否加珍珠和是否加冰是可选的。使用建造者模式表示如下：
#include <iostream>
using namespace std;

class MilkTea
{
private:
    string type;
    string size;
    bool pearl;
    bool ice;

public:
    MilkTea(/* args */);
    ~MilkTea();
    string SetType(string in_type) { type = in_type; }
    string SetSize(string in_size) { size = in_size; }
    bool SetPearl(bool choice) { pearl = choice; }
    bool SetIce(bool choice) { ice = choice; }
};

//抽象一个bulider
class Builder
{
private:
public:
    Builder();
    ~Builder();
    virtual void SetMilkTeaType();
    virtual void SetMilkTeaSize();
    virtual void SetMilkTeaPearl();
    virtual void SetMilkTeaIce();
    virtual MilkTea* GetMilkTea();
};

//中杯奶茶
class MeddleMilkBuilder : public Builder
{
private:
    MilkTea* m_milk_tea;
public:
    MeddleMilkBuilder()
    {
        m_milk_tea = new MilkTea();
    }
    virtual void SetMilkTeaType() { m_milk_tea->SetType("果粒橙"); };
    virtual void SetMilkTeaSize() { m_milk_tea->SetSize("中杯"); };
    virtual void SetMilkTeaPearl() { m_milk_tea->SetPearl(false); };
    virtual void SetMilkTeaIce() { m_milk_tea->SetIce(true); };
    virtual MilkTea *GetMilkTea() { return m_milk_tea; };
    ~MeddleMilkBuilder();
};

//大杯奶茶
class LargeMilkBuilder : public Builder
{
private:
    MilkTea *m_milk_tea;

public:
    LargeMilkBuilder()
    {
        m_milk_tea = new MilkTea();
    }
    virtual void SetMilkTeaType() { m_milk_tea->SetType("乌龙茶"); };
    virtual void SetMilkTeaSize() { m_milk_tea->SetSize("大杯"); };
    virtual void SetMilkTeaPearl() { m_milk_tea->SetPearl(true); };
    virtual void SetMilkTeaIce() { m_milk_tea->SetIce(true); };
    virtual MilkTea *GetMilkTea() { return m_milk_tea; };
    ~LargeMilkBuilder();
};

//创建工厂类
class Factory
{
private:
    Builder* m_builder;
public:
    Factory(Builder *builder) { m_builder = builder; };
    ~Factory();
    void AssambleMileTea()
    {
        m_builder->SetMilkTeaIce();
        m_builder->SetMilkTeaPearl();
        m_builder->SetMilkTeaSize();
        m_builder->SetMilkTeaType();
    }
    MilkTea *GetMilkTea() { return m_builder->GetMilkTea(); };
};

int main(int argc, char const *argv[])
{
    //创建大杯奶茶类builder
    Builder* m_builder = new LargeMilkBuilder();
    //创建工厂
    Factory *m_factory = new Factory(m_builder);
    //使用工厂创建奶茶
    m_factory->AssambleMileTea();
    //获取奶茶
    MilkTea* m_milktea = m_factory->GetMilkTea();
    

    return 0;
}



