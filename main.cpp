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

enum class FeedingMannerEnum : int
{
    Meat,
    Fish,
    Pate,
    None
};

class FeedingStrategy
{
public:
  virtual ~FeedingStrategy() {}
  virtual void Feed() = 0;
};

class MeatFeedingStrategy : public FeedingStrategy
{
  void Feed() { cout << "Feed pet with meat"; }
};

class FishFeedingStrategy : public FeedingStrategy
{
  void Feed() { cout << "Feed pet with fish"; }
};

class PateFeedingStrategy : public FeedingStrategy
{
  void Feed() { cout << "Feed pet with pate"; }
};


// Фабричный метод для создания стратегий
FeedingStrategy *CreateFeedingStrategy(FeedingMannerEnum feedingManner)
{
  switch(feedingManner)
  {
    case FeedingMannerEnum::Meat: return new MeatFeedingStrategy;
    case FeedingMannerEnum::Fish: return new FishFeedingStrategy;
    case FeedingMannerEnum::Pate: return new PateFeedingStrategy;

    default: return nullptr;
  }
}

class Pet
{
private:
    PetAge Age;
    PetWeight Weight;
    string Pocritie;
    double Length;

    FeedingStrategy *FeedingManner;

    void DoFeedUsingStrategy()
    {
      if(FeedingManner == nullptr)
      {
        // Способ съедания не задан, ничего не делаем
        cout << "Do nothing!";
        return;
      }
      else
      {
        // Съесть заданным способом
        FeedingManner->Feed();
      }
    }

    void DetectKindOrNot()
    {
      if(IsKind())
      {
          cout << "KIND";
      }
      else
      {
          cout << "BAD";
      }
    }

protected:
    bool PetIsKind;

public:
    //Pet(PetAge age, double weight, double length);
    //Pet::Pet(PetAge age, double weight, double length) : Age(age), Weight(weight), Pocritie("wool"), Length(length), PetIsKind(false)
    Pet(PetAge age, PetWeight weight, double length) : Age(age), Weight(weight), Pocritie("wool"), Length(length), PetIsKind(false), FeedingManner(nullptr)
{
    PetIsKind = static_cast<bool>(rand()%2);
}
    virtual ~Pet()
    {
        if(FeedingManner != nullptr) delete FeedingManner;
    }

    // Функция с реализацией
    bool IsKind() const { return PetIsKind; }

    PetAge GetAge() const { return Age; }
    PetWeight GetWeight() const { return Weight; }
    string GetPocritie() const { return Pocritie; }
    double GetLength() const { return Length; }

    //virtual void Feed() = 0;

    virtual void PrintType() = 0;
    virtual void Prepare() = 0;

    void Feed()
    {
        // 1. Вывести название животного
        PrintType();
        cout << " : ";

        // 2. Определить, доброе животное или нет
        DetectKindOrNot();
        cout << " : ";

        // 2.1 Подготовить еду
        Prepare();
        cout << " : ";

        // 3. Если доброе, съесть с использованием выбранной стратегии
        DoFeedUsingStrategy();

        // 4. Конец алгоритма
        cout << endl;
    }

    void SetFeedingManner(FeedingStrategy *feedingManner) { FeedingManner = feedingManner; }
};

class Dog : public Pet
{
public:
    Dog();
    ~Dog();

    string GetPocritie() const;

    void Feed();
    void PrintType() { cout << "Dog";}
    void Prepare() { cout << "Prepare food with a knife"; }
};
// Реализация конструктора
Dog::Dog() : Pet(PetAge::Five, PetWeight::Fifteen, 1.2)
{
    SetFeedingManner(CreateFeedingStrategy(FeedingMannerEnum::Meat));
}
void Dog::Feed()
{
    cout << "Feeding Weasel..." << endl;
}
Dog::~Dog()
{
    cout << "Deleting Dog..." << endl;
}

class Cat : public Pet
{
public:
    Cat();
    ~Cat();

    string GetPocritie() const;

    void Feed();
    void PrintType() { cout << "Cat"; }
    void Prepare() { cout << "Prepare food using special tools"; }
};

Cat::Cat() : Pet(PetAge::Three, PetWeight::Three, 0.7)
{
    SetFeedingManner(CreateFeedingStrategy(FeedingMannerEnum::Fish));
}
void Cat::Feed()
{
    cout << "Feeding Cat..." << endl;
}
Cat::~Cat()
{
    cout << "Deleting Cat..." << endl;
}

class Weasel : public Pet
{
public:
    Weasel();
    ~Weasel();

    string GetPocritie() const;

    void Feed();
    void PrintType() { cout << "Weasel"; }
    void Prepare() { cout << "Prepare food using a meat grinder"; }
};

Weasel::Weasel() : Pet(PetAge::One, PetWeight::One, 0.2)
{
    SetFeedingManner(CreateFeedingStrategy(FeedingMannerEnum::Pate));
}
void Weasel::Feed()
{
    cout << "Feeding Weasel..." << endl;
}
Weasel::~Weasel()
{
    cout << "Deleting Weasel..." << endl;
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

void FeedAll(Iterator<Pet*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Pet *currentPet = it->GetCurrent();
        currentPet->Feed();
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    size_t N = 10;

    ArrayClass<Pet*> petArray;
    for(size_t i=0; i<N; i++)
    {
        int pet_num = rand()%3+1; // Число от 1 до 3
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
    cout << endl << "Feeding all in a simple loop:" << endl;
    for(size_t i=0; i<petArray.Size(); i++)
    {
        Pet *currentPet = petArray[i];
        currentPet->Feed();
    }

    // Обход всех элементов при помощи итератора
    cout << endl << "Feeding all using iterator:" << endl;
    Iterator<Pet*> *allIt = petArray.GetIterator();
    FeedAll(allIt);
    delete allIt;

    // Обход всех добрых животных
    cout << endl << "Feeding all kind using iterator:" << endl;
    Iterator<Pet*> *kindIt = new PetKindDecorator(petArray.GetIterator(), true);
    FeedAll(kindIt);
    delete kindIt;

    // Обход всех пятилетних животных
    cout << endl << "Feeding all five age using iterator:" << endl;
    Iterator<Pet*> *fiveIt = new PetAgeDecorator(petArray.GetIterator(), PetAge::Five);
    FeedAll(fiveIt);
    delete fiveIt;

    // Обход всех килограммовых животных
    cout << endl << "Feeding all one weight using iterator:" << endl;
    Iterator<Pet*> *oneIt = new PetWeightDecorator(petArray.GetIterator(), PetWeight::One);
    FeedAll(oneIt);
    delete oneIt;

    // Обход всех добрых пятилетних животных
    cout << endl << "Feeding all kind five age using iterator:" << endl;
    Iterator<Pet*> *kindFiveIt = new PetKindDecorator(new PetAgeDecorator(petArray.GetIterator(), PetAge::Five), true);
    FeedAll(kindFiveIt);
    delete kindFiveIt;

    // Обход всех добрых килограммовых животных
    cout << endl << "Feeding all kind one weight using iterator:" << endl;
    Iterator<Pet*> *kindOneIt = new PetKindDecorator(new PetWeightDecorator(petArray.GetIterator(), PetWeight::One), true);
    FeedAll(kindOneIt);
    delete kindOneIt;

    // Демонстрация работы адаптера
    cout << endl << "Feeding all kind five age using adapted iterator (another container):" << endl;
    Iterator<Pet*> *adaptedIt = new ConstIteratorAdapter<std::list<Pet*>, Pet*>(&petVector);
    Iterator<Pet*> *adaptedFiveIt = new PetKindDecorator(new PetAgeDecorator(adaptedIt, PetAge::Five), true);
    FeedAll(adaptedFiveIt);
    delete adaptedFiveIt;

    return 0;
}
