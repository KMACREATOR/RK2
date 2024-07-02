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

using ::testing::AtLeast;

/*
 * Product
 * products implement the same interface so that the classes can refer
 * to the interface not the concrete product
 */
class Product
{
public:
  virtual ~Product() {}

  virtual std::string getName() = 0;
  // ...
};

// MockProduct для класса Mock
class MockProduct : public Product {
public:
  MOCK_METHOD(std::string, getName, (), (override));
};

// сразу же тестируем
TEST(ProductTest, PrintingCheck){
  MockProduct prod;
  EXPECT_CALL(prod, getName())
    .Times(AtLeast(1));
  prod.getName();
}

/*
 * Concrete Product
 * define product to be created
 */
class ConcreteProductA : public Product
{
public:
  ~ConcreteProductA() {}

  std::string getName() override
  {
    return "type A";
  }
  // ...
};

TEST(TestProducts, ProductA){
  ConcreteProductA PA1;
  EXPECT_STREQ(PA1.getName().c_str(), "type A");
}

/*
 * Concrete Product
 * define product to be created
 */
class ConcreteProductB : public Product
{
public:
  ~ConcreteProductB() {}
  
  std::string getName() override
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
  
  virtual void removeProduct(Product* product) = 0;
  
  // ...
};

// MockCreator класс для Creator
class MockCreator : public Creator {
public:
  MOCK_METHOD(Product*, createProductA, (), (override));
  MOCK_METHOD(Product*, createProductB, (), (override));
  MOCK_METHOD(void, removeProduct, (Product* product), (override));
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
  
  Product* createProductA() override
  {
    return new ConcreteProductA();
  }
  
  Product* createProductB() override
  {
    return new ConcreteProductB();
  }
  
  void removeProduct(Product* product) override
  {
    delete product;
  }
  // ...
};

// тестируем ConcreteCreator
TEST(ConcreteTests, CreatorTest){
  ConcreteCreator creator;
  Product* p1 = creator.createProductA();
  EXPECT_NE(p1, nullptr);
  creator.removeProduct(p1);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  Creator* creator = new ConcreteCreator();
  
  Product* p1 = creator->createProductA();
  std::cout << "Product: " << p1->getName() << std::endl;
  creator->removeProduct(p1);
  
  Product* p2 = creator->createProductB();
  std::cout << "Product: " << p2->getName() << std::endl;
  creator->removeProduct(p2);
  
  delete creator;
  return RUN_ALL_TESTS();
}
