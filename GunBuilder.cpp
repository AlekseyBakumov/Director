#include <iostream>
#include <vector>
#include <string>

class Product {
public:
    std::vector<std::string> parts;
    std::string name;
    void _print()
    {
        std::cout << "Name:" << name << std::endl;
        std::cout << "Parts:" << std::endl;
        for (auto iter = parts.begin(); iter != parts.end(); iter++)
            std::cout << *iter << std::endl;
        std::cout << std::endl;
    }
};

class Gun : public Product
{
public:
    void Print()
    {
        std::cout << "Gun." << std::endl;
        _print();
    }
};

class Docs : public Product
{
public:
    void Print()
    {
        std::cout << "Documentation." << std::endl;
        _print();
    }
};

class Builder {
public:
    virtual ~Builder() {}
    // Required
    virtual void ProduceBarrel()       const = 0;
    virtual void ProduceRecoilSpring() const = 0;
    virtual void ProduceHandguard()    const = 0;
    virtual void ProduceRearGrip()     const = 0;
    // Optional
    virtual void ProduceFrontGrip()    const = 0;
    virtual void ProduceSilencer()     const = 0;
    virtual void ProduceScope()        const = 0;

    void BuildBase()
    {
        ProduceBarrel();
        ProduceRecoilSpring();
        ProduceHandguard();
        ProduceRearGrip();
    }

    virtual void SetProductName(std::string name) = 0;
};

class GunBuilder : public Builder {
private:
    Gun* result;

public:

    GunBuilder()
    {
        this->Reset();
    }

    ~GunBuilder()
    {
        delete result;
    }

    void Reset() {
        this->result = new Gun();
    }
    void ProduceBarrel()const override {
        this->result->parts.push_back("Mid range barrel");
    }
    void ProduceRecoilSpring()const override {
        this->result->parts.push_back("Strong recoil spring");
    }
    void ProduceHandguard()const override {
        this->result->parts.push_back("Plastic handguard");
    }
    void ProduceRearGrip()const override {
        this->result->parts.push_back("Plastic pistol grip");
    }
    void ProduceFrontGrip()const override {
        this->result->parts.push_back("Plastic tactical grip");
    }
    void ProduceSilencer()const override {
        this->result->parts.push_back("Spec ops silencer");
    }
    void ProduceScope()const override {
        this->result->parts.push_back("Holographic sight");
    }

    void SetProductName(std::string name) { result->name = name; }

    Product* GetProduct() {
        Gun* result = this->result;
        this->Reset();
        return result;
    }
};

class DocsBuilder : public Builder {
private:
    Docs* result;

public:

    DocsBuilder()
    {
        this->Reset();
    }

    ~DocsBuilder()
    {
        delete result;
    }

    void Reset() {
        this->result = new Docs();
    }
    void ProduceBarrel()const override {
        this->result->parts.push_back("[824] Barrel B-12SC");
    }
    void ProduceRecoilSpring()const override {
        this->result->parts.push_back("[492] Recoil Spring RS-55N");
    }
    void ProduceHandguard()const override {
        this->result->parts.push_back("[729] HG 2A Plastic");
    }
    void ProduceRearGrip()const override {
        this->result->parts.push_back("[428] GRIP 22-R Plastic");
    }
    void ProduceFrontGrip()const override {
        this->result->parts.push_back("[430] GRIP 24-R Tacs Plastic");
    }
    void ProduceSilencer()const override {
        this->result->parts.push_back("[934] SIL 001-B Tacs");
    }
    void ProduceScope()const override {
        this->result->parts.push_back("[026] HS \"Red Dot\"");
    }

    Product* GetProduct() {
        Docs* result = this->result;
        this->Reset();
        return result;
    }

    void SetProductName(std::string name) { result->name = name; }
};

class Director {
private:
    Builder* builder;

public:
    void set_builder(Builder* builder) {
        this->builder = builder;
    }
    
    void BuildGun() {
        this->builder->BuildBase();
        this->builder->SetProductName("Std AR");
    }
    void BuildTacticalGun() {
        this->builder->BuildBase();
        this->builder->SetProductName("Tactic AR");
        this->builder->ProduceFrontGrip();
        this->builder->ProduceScope();
    }
    void CreateBlueprint()
    {
        this->builder->BuildBase();
        this->builder->SetProductName("AR Blueprint");
        this->builder->ProduceFrontGrip();
        this->builder->ProduceSilencer();
        this->builder->ProduceScope();
    }
};

void ClientCode(Director& director)
{
    GunBuilder* gun_b = new GunBuilder();
    DocsBuilder* doc_b = new DocsBuilder();
    director.set_builder(gun_b);


    std::cout << "Standard gun:\n";
    director.BuildGun();
    Gun* p1 = static_cast<Gun*>(gun_b->GetProduct());
    p1->Print();
    delete p1;

    std::cout << "Tactical gun:\n";
    director.BuildTacticalGun();
    Gun* p2 = static_cast<Gun*>(gun_b->GetProduct());
    p2->Print();
    delete p2;

    director.set_builder(doc_b);

    std::cout << "Gun documentation:\n";
    director.CreateBlueprint();
    Docs* p3 = static_cast<Docs*>(doc_b->GetProduct());
    p3->Print();
    delete p3;
}

int main() {
    Director* director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}

