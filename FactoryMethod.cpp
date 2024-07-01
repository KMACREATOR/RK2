/*
 * C++ Design Patterns: Factory Method
 * Author: Jakub Vojvoda [github.com/JakubVojvoda]
 * 2016
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
/*
 * Product
 * products implement the same interface so that the classes can refer
 * to the interface not the concrete product
 */

using ::testing::AtLeast;

class Product
{
public:
  virtual ~Product() {}

  virtual std::string getName() = 0;
  // ...
};


//MockProduct для класса Mock
class MockProduct : public Product {
	MOCK_METHOD(std::string, getName(), (), (override));
};

//сразу же тестируем

TEST(ProductTest, PrintingCheck){
	MockProduct prod;
	prod.getName();
	EXPECT_CALL(prod, getName())
		.Times(AtLeast(1));
}



/*
 * Concrete Product
 * define product to be created
 */
class ConcreteProductA : public Product
{
public:
  ~ConcreteProductA() {}

  std::string getName()
  {
    return "type A";
  }
  // ...
};

TEST(TestProducts, ProductA){
	ConcreteProductA PA1;
	EXPECT_STREQ(PA1.getName, "type A");
}

/*
 * Concrete Product
 * define product to be created
 */
class ConcreteProductB : public Product
{
public:
  ~ConcreteProductB() {}
  
  std::string getName()
  {
    return "type B";
  }
  // ...
};

/*
 * Creator
 * contains the implementation for all of the methods
 * to manipulate products except for the factory method
 */
class Creator
{
public:
  virtual ~Creator() {}
  
  virtual Product* createProductA() = 0;
  virtual Product* createProductB() = 0;
  
  virtual void removeProduct( Product *product ) = 0;
  
  // ...
};

//MockCreator класс для Creator

class MockCreator : public Creator {
	MOCKMETHOD(Product*, createProductA (), (override));
		
};


/*
 * Concrete Creator
 * implements factory method that is responsible for creating
 * one or more concrete products ie. it is class that has
 * the knowledge of how to create the products
 */
class ConcreteCreator : public Creator
{
public:
  ~ConcreteCreator() {}
  
  Product* createProductA()
  {
    return new ConcreteProductA();
  }
  
  Product* createProductB()
  {
    return new ConcreteProductB();
  }
  
  void removeProduct( Product *product )
  {
    delete product;
  }
  // ...
};

//тестируем ConcreteCreator
TEST (ConcreteTests, CreatorTets){
	ConcreteCreator concreator1;
	ConcreteCreator concreator2;	

}

int main()
{
  Creator *creator = new ConcreteCreator();
  
  Product *p1 = creator->createProductA();
  std::cout << "Product: " << p1->getName() << std::endl;
  creator->removeProduct( p1 );
  
  Product *p2 = creator->createProductB();
  std::cout << "Product: " << p2->getName() << std::endl;
  creator->removeProduct( p2 );
  
  ::testing::InitGoogleTest(&argc, argv);
  delete creator;
  return RUN_ALL_TESTS();
}
