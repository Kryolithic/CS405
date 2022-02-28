// CS405 Unit Test Milestone
// Modified By: Gary Clark
// ******SNHU*************
// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue


// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}


TEST_F(CollectionTest, CanAddToEmptyVector)
{
    //assert that collection is empty and size = 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    //assert collection is not empty after calling add_entries function
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);
}


TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    int prevSize = collection->size(); //stores initial size of collection
    add_entries(5); //add five values to collection

    ASSERT_FALSE(collection->empty()); //asserts collection is not empty
    ASSERT_EQ(collection->size(), prevSize + 5); //asserts collection is 5 values larger
}


TEST_F(CollectionTest, MaxSizeGrEqEntry)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //verfies max size of collection >= the size of collection for collections with 0, 1, 5, 10 entries
    EXPECT_GE(collection->max_size(), collection->size());
    add_entries(1); //adds 1 to collection
    EXPECT_GE(collection->max_size(), collection->size());
    add_entries(4); //adds 4 more values for a total of 5
    EXPECT_GE(collection->max_size(), collection->size());
    add_entries(5); //adds 5 more values for a total of 10
    EXPECT_GE(collection->max_size(), collection->size());

}


TEST_F(CollectionTest, CapacityGeEqEntry)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //verifies capacity of collection >= to size of collection with 0, 1, 5, 10 entries
    EXPECT_GE(collection->capacity(), collection->size());
    add_entries(1); //adds 1 entry to collection
    EXPECT_GE(collection->capacity(), collection->size());
    add_entries(4); //adds 4 more entries for total of 5
    EXPECT_GE(collection->capacity(), collection->size());
    add_entries(5); //adds 5 more entries for total of 10
    EXPECT_GE(collection->capacity(), collection->size());
}


TEST_F(CollectionTest, ResizeIncreaseCollection)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //adds 10 entries to collection
    add_entries(10);
    EXPECT_EQ(collection->size(), 10); //verfies size of collection is now 10
    collection->resize(15); //resize collection to 15
    EXPECT_LE(10, collection->size()); //verify that previous size of 10 is now less than the size of collection
}


TEST_F(CollectionTest, ResizeDecreaseCollection)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //add 5 entries to collection
    add_entries(5);
    EXPECT_EQ(collection->size(), 5); //verify collection size is 5
    collection->resize(1); //resize collection to 1
    EXPECT_LE(collection->size(), 5); //verify that collection size is less than prev size of 5
}


TEST_F(CollectionTest, ResizeCollectionToZero)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //add 10 entries to collection
    add_entries(10);
    EXPECT_EQ(collection->size(), 10);//verify size is now 10
    collection->resize(0); //resize collection to 0
    EXPECT_EQ(collection->size(), 0); //verify collection size is now 0
}


TEST_F(CollectionTest, ClearCollection)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //add 5 entries to collection
    add_entries(5);
    EXPECT_EQ(collection->size(), 5);//verify size is now 5
    collection->clear(); //call clear() function on collection
    ASSERT_TRUE(collection->empty()); //assert collection is now empty
    ASSERT_EQ(collection->size(), 0); //assert that collection size is now 0
}


TEST_F(CollectionTest, EraseCollection)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //add 5 values to collection
    add_entries(5);
    EXPECT_EQ(collection->size(), 5); //verify size is 5
    collection->erase(collection->begin(), collection->end()); //call erase() with start at collection->begin and end at collection->end
    ASSERT_TRUE(collection->empty()); //assert collection is now empty
    ASSERT_EQ(collection->size(), 0); //assert collection size is now 0
}


TEST_F(CollectionTest, ReserveIncreaseCapacityOnly)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //call reserve() function on collection passing value of 100
    collection->reserve(100);
    EXPECT_GE(collection->capacity(), 100); //verify capacity is now >= to 100
    ASSERT_EQ(collection->size(), 0); //assert that size of collection remains unchanged
}

//NEGATIVE TEST
TEST_F(CollectionTest, AccessNonExistentItem)
{
    //asserts that a collection with 5 values throws out_of_range exception when accessing collection.at(10)
    ASSERT_THROW({
        add_entries(5);
        int n = collection->at(10); }
    , std::out_of_range);
}


TEST_F(CollectionTest, PopBackValue)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    //adds 5 values to collection
    add_entries(5);
    EXPECT_EQ(collection->size(), 5); //verify size is now 5
    collection->pop_back(); //call pop_back()
    EXPECT_EQ(collection->size(), 4); //verify pop_back() removed 1 entry and size is now 4
}

TEST_F(CollectionTest, PushBackValue)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
    //push back 10
    collection->push_back(10);
    ASSERT_EQ(collection->at(0), 10); //asserts that value in first position of collection is now 10
}

//NEGATIVE TEST
TEST_F(CollectionTest, NegativeIntegerEntry)
{
    //asserts collection starts empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
    
    //verifies an exception is thrown when passing invalid parameter to at() function
    EXPECT_ANY_THROW(int n = collection->at(-5));
}