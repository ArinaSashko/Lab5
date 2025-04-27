#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "PatternTemplates.h"
#include <vector>
#include <list>

using namespace std;

enum class PetAge : int
{
    One,
    Three,
    Five,
    Unknown
};
enum class PetWeight : int
{
    Fifteen,
    Three,
    One,
    Unknown
};

class Pet
{
private:
    PetAge Age;
    PetWeight Weight;
    string Pocritie;
    double Length;

protected:
    bool PetIsKind;

public:
    //Pet(PetAge age, double weight, double length);
    //Pet::Pet(PetAge age, double weight, double length) : Age(age), Weight(weight), Pocritie("wool"), Length(length), PetIsKind(false)
    Pet(PetAge age, PetWeight weight, double length) : Age(age), Weight(weight), Pocritie("wool"), Length(length), PetIsKind(false)
{
    PetIsKind = static_cast<bool>(rand()%2);
}
    virtual ~Pet();

    // Функция с реализацией
    bool IsKind() const { return PetIsKind; }

    PetAge GetAge() const { return Age; }
    PetWeight GetWeight() const { return Weight; }
    string GetPocritie() const { return Pocritie; }
    double GetLength() const { return Length; }

    virtual void Touch() = 0;
    virtual void Feed() = 0;
    virtual void Walk() = 0;
};

// Реализация деструктора
Pet::~Pet()
{
    cout << "Deleting Pet..." << endl;
}

class Dog : public Pet
{
public:
    Dog();
    ~Dog();

    string GetPocritie() const;

    void Touch();
    void Feed();
    void Walk();
};
// Реализация конструктора
Dog::Dog() : Pet(PetAge::Five, PetWeight::Fifteen, 1.2)
{
    PetIsKind = true;

    cout << "Creating Dog..." << endl;
}
// Реализация деструктора
Dog::~Dog()
{
    cout << "Deleting Dog..." << endl;
}
string Dog::GetPocritie() const
{
    cout << "Dog Pocritie: " << Pet::GetPocritie() << endl;
    return Pet::GetPocritie();
}
void Dog::Touch()
{
    cout << "Touching Dog..." << endl;
}
void Dog::Feed()
{
   cout << "Feeding Dog..." << endl;
}
void Dog::Walk()
{
   cout << "Walking Dog..." << endl;
}

class Cat : public Pet
{
public:
    Cat();
    ~Cat();

    string GetPocritie() const;

    void Touch();
    void Feed();
    void Walk();
};

Cat::Cat() : Pet(PetAge::Three, PetWeight::Three, 0.7)
{
    PetIsKind = true;

    cout << "Creating Cat..." << endl;
}

Cat::~Cat()
{
    cout << "Deleting Cat..." << endl;
}
string Cat::GetPocritie() const
{
    cout << "Cat Pocritie: " << Pet::GetPocritie() << endl;
    return Pet::GetPocritie();
}
void Cat::Touch()
{
    cout << "Touching Cat..." << endl;
}
void Cat::Feed()
{
    cout << "Feeding Cat..." << endl;
}
void Cat::Walk()
{
    cout << "Walking Cat..." << endl;
}

class Weasel : public Pet
{
public:
    Weasel();
    ~Weasel();

    string GetPocritie() const;

    void Touch();
    void Feed();
    void Walk();
};

Weasel::Weasel() : Pet(PetAge::One, PetWeight::One, 0.2)
{
    PetIsKind = true;

    //cout << "Creating Weasel..." << endl;
}

Weasel::~Weasel()
{
    //cout << "Deleting Weasel..." << endl;
}
string Weasel::GetPocritie() const
{
   // cout << "Weasel Pocritie: " << Pet::GetPocritie() << endl;
    return Pet::GetPocritie();
}
void Weasel::Touch()
{
    cout << "Touching Weasel..." << endl;
}
void Weasel::Feed()
{
    cout << "Feeding Weasel..." << endl;
}
void Weasel::Walk()
{
    cout << "Walking Weasel..." << endl;
}

enum class PetType : int
{
    Dog = 1,
    Cat = 2,
    Weasel = 3,

    Undefined = 0
};

Pet *CreatePet(PetType type)
{
    Pet *newPet = nullptr;

    if(type == PetType::Dog)
    {
        newPet = new Dog;
    }
    else if(type == PetType::Cat)
    {
        newPet = new Cat;
    }
    else if(type == PetType::Weasel)
    {
        newPet = new Weasel;
    }

    return newPet;
}

class PetAgeDecorator : public IteratorDecorator<class Pet*>
{
private:
    PetAge TargetAge;

public:
    PetAgeDecorator(Iterator<Pet*> *it, PetAge age)
    : IteratorDecorator<Pet*>(it), TargetAge(age) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetAge() != TargetAge)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetAge() != TargetAge);
    }
};

//
class PetWeightDecorator : public IteratorDecorator<class Pet*>
{
private:
    PetWeight TargetWeight;

public:
    PetWeightDecorator(Iterator<Pet*> *it, PetWeight weight)
    : IteratorDecorator<Pet*>(it), TargetWeight(weight) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetWeight() != TargetWeight)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetWeight() != TargetWeight);
    }
};
//
class PetKindDecorator : public IteratorDecorator<class Pet*>
{
private:
    bool TargetKind;

public:
    PetKindDecorator(Iterator<Pet*> *it, bool isKind)
    : IteratorDecorator<Pet*>(it), TargetKind(isKind) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->IsKind() != TargetKind)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->IsKind() != TargetKind);
    }
};

void TouchAll(Iterator<Pet*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Pet *currentPet = it->GetCurrent();
        currentPet->Touch();
    }
}
void FeedAll(Iterator<Pet*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Pet *currentPet = it->GetCurrent();
        currentPet->Feed();
    }
}
void WalkAll(Iterator<Pet*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Pet *currentPet = it->GetCurrent();
        currentPet->Walk();
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    size_t N = 10;

    ArrayClass<Pet*> petArray;
    for(size_t i=0; i<N; i++)
    {
        int pet_num = rand()%3+1; // Число от 1 до 3 (случайный фрукт)
        PetType pet_type = static_cast<PetType>(pet_num);
        Pet *newPet = CreatePet(pet_type);
        petArray.Add(newPet);
    }

    cout << endl;
    wcout << L"Размер массива животных: " << petArray.Size() << endl;

    list<Pet*> petVector;
    cout << endl;
    for(size_t i=0; i<N; i++)
    {
        int pet_num = rand()%3+1; // Число от 1 до 3
        PetType pet_type = static_cast<PetType>(pet_num);
        Pet *newPet = CreatePet(pet_type);
        petVector.push_back(newPet);
    }

    cout << endl;
    wcout << L"Размер списка животных: " << petVector.size() << endl;

    // Обход в простом цикле
    cout << endl << "Touching all in a simple loop:" << endl;
    for(size_t i=0; i<petArray.Size(); i++)
    {
        Pet *currentPet = petArray[i];
        currentPet->Touch();
    }

    // Обход всех элементов при помощи итератора
    cout << endl << "Touching all using iterator:" << endl;
    Iterator<Pet*> *allIt = petArray.GetIterator();
    TouchAll(allIt);
    delete allIt;

    // Обход всех добрых животных
    cout << endl << "Feeding all kind using iterator:" << endl;
    Iterator<Pet*> *kindIt = new PetKindDecorator(petArray.GetIterator(), true);
    FeedAll(kindIt);
    delete kindIt;

    // Обход всех пятилетних животных
    cout << endl << "Walking all five age using iterator:" << endl;
    Iterator<Pet*> *fiveIt = new PetAgeDecorator(petArray.GetIterator(), PetAge::Five);
    WalkAll(fiveIt);
    delete fiveIt;

    // Обход всех килограммовых животных
    cout << endl << "Touching all one weight using iterator:" << endl;
    Iterator<Pet*> *oneIt = new PetWeightDecorator(petArray.GetIterator(), PetWeight::One);
    TouchAll(oneIt);
    delete oneIt;

    // Обход всех добрых пятилетних животных
    cout << endl << "Feeding all kind five age using iterator:" << endl;
    Iterator<Pet*> *kindFiveIt = new PetKindDecorator(new PetAgeDecorator(petArray.GetIterator(), PetAge::Five), true);
    FeedAll(kindFiveIt);
    delete kindFiveIt;

    // Обход всех добрых килограммовых животных
    cout << endl << "Walking all kind one weight using iterator:" << endl;
    Iterator<Pet*> *kindOneIt = new PetKindDecorator(new PetWeightDecorator(petArray.GetIterator(), PetWeight::One), true);
    WalkAll(kindOneIt);
    delete kindOneIt;

    // Демонстрация работы адаптера
    cout << endl << "Touching all kind five age using adapted iterator (another container):" << endl;
    Iterator<Pet*> *adaptedIt = new ConstIteratorAdapter<std::list<Pet*>, Pet*>(&petVector);
    Iterator<Pet*> *adaptedFiveIt = new PetKindDecorator(new PetAgeDecorator(adaptedIt, PetAge::Five), true);
    TouchAll(adaptedFiveIt);
    delete adaptedFiveIt;

    return 0;
}
