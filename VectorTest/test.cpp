#include "pch.h"
#include "../Vector/src/Vector.h"
#include <vector>

namespace {

    class VectorTest : public ::testing::Test {

    public:
        VectorTest() : vec_int_(), vec_string_(), vec_obj_() {

        }

    protected:
        vector::Vector<int> vec_int_;
        vector::Vector<std::string> vec_string_;
        vector::Vector<vector::Vector<int>> vec_obj_;

    };

    //testing initialization size, max_size/capacity
    TEST_F(VectorTest, initialization) {
        EXPECT_EQ(vec_int_.size(), 0);
        EXPECT_EQ(vec_string_.size(), 0);
        EXPECT_EQ(vec_obj_.size(), 0);

        EXPECT_EQ(vec_int_.max_size(), 0);
        EXPECT_EQ(vec_string_.max_size(), 0);
        EXPECT_EQ(vec_obj_.max_size(), 0);

        EXPECT_EQ(vec_int_.capacity(), 0);
        EXPECT_EQ(vec_string_.capacity(), 0);
        EXPECT_EQ(vec_obj_.capacity(), 0);

        EXPECT_EQ(vec_int_.empty(), true);
        EXPECT_EQ(vec_string_.empty(), true);
        EXPECT_EQ(vec_obj_.empty(), true);
    }

    //clearing empty vectors, vectors with elements
    TEST_F(VectorTest, clear) {
        vec_int_.clear();
        vec_string_.clear();
        vec_obj_.clear();
        EXPECT_EQ(vec_int_.empty(), true);
        EXPECT_EQ(vec_string_.empty(), true);
        EXPECT_EQ(vec_obj_.empty(), true);
        
        vec_int_.push_back(3);
        vec_int_.push_back(30);
        vec_int_.clear();
        EXPECT_EQ(vec_int_.size(), 0);
        vec_string_.push_back("DOG");
        vec_string_.push_back("CAT");
        vec_string_.clear();
        EXPECT_EQ(vec_string_.size(), 0);
        
        vector::Vector<int> v1;
        vector::Vector<int> v2;
        
        vec_obj_.push_back(v1);
        vec_obj_.push_back(v2);
        vec_obj_.clear();
        EXPECT_EQ(vec_obj_.empty(), true);
        
        
    }

    TEST_F(VectorTest, reserve) {
        vec_int_.reserve(10);
        vec_string_.reserve(0);
        vec_obj_.reserve(1);
        EXPECT_EQ(vec_int_.capacity(), 10);
        EXPECT_EQ(vec_int_.max_size(), 10);
        EXPECT_EQ(vec_string_.capacity(), 0);
        EXPECT_EQ(vec_string_.max_size(), 0);
        EXPECT_EQ(vec_obj_.capacity(), 1);
        EXPECT_EQ(vec_obj_.max_size(), 1);
    }

    //insert elements using push_back 
    TEST_F(VectorTest, push_back) {
        vec_int_.clear();
        vec_string_.clear();
        vec_obj_.clear();


        vec_int_.push_back(2);
        vec_int_.push_back(-5);
        vec_int_.push_back(2);
        EXPECT_EQ(-5, vec_int_[1]);
        EXPECT_EQ(2, vec_int_[0]);
        EXPECT_EQ(3, vec_int_.size());

        vec_string_.push_back("Dog");
        vec_string_.push_back("cat");
        EXPECT_EQ(std::string("Dog"), vec_string_[0]);
        EXPECT_EQ(std::string("cat"), vec_string_[1]);
        EXPECT_EQ(2, vec_string_.size());

        vector::Vector<int> v1;
        vector::Vector<int> v2;
        v1.push_back(1);
        v2.push_back(2);
        vec_obj_.push_back(v1);
        vec_obj_.push_back(v2);
        EXPECT_EQ(1, vec_obj_[0].at(0));
        EXPECT_EQ(2, vec_obj_[1].at(0));
    }

    //access elements using [], at(unsigned in), front(), back()
    TEST_F(VectorTest, access_elements) {
        vec_int_.clear();
        vec_string_.clear();
        vec_obj_.clear();

        vec_int_.push_back(3);
        vec_int_.push_back(10);
        vec_int_.push_back(0);
        EXPECT_EQ(0, vec_int_[2]);
        EXPECT_EQ(3, vec_int_.front());
        EXPECT_EQ(0, vec_int_.back());
        EXPECT_EQ(10, vec_int_.at(1));
        
        vec_string_.push_back("Cat");
        vec_string_.push_back("Dog");
        EXPECT_EQ(std::string("Cat"), vec_string_[0]);
        EXPECT_EQ(std::string("Cat"), vec_string_.at(0));
        EXPECT_EQ(std::string("Cat"), vec_string_.front());
        EXPECT_EQ(std::string("Dog"), vec_string_.back());

        vector::Vector<int> v1;
        vector::Vector<int> v2;
        v1.push_back(1);
        v2.push_back(2);
        vec_obj_.push_back(v1);
        vec_obj_.push_back(v2);
        EXPECT_EQ(1, vec_obj_.at(0)[0]);
        EXPECT_EQ(2, vec_obj_[1].at(0));
        EXPECT_EQ(1, vec_obj_.front().front());
        EXPECT_EQ(2, vec_obj_.back().back());


    }

    TEST_F(VectorTest, resize) {
        vec_int_.clear();
        vec_int_.resize(0);
        EXPECT_EQ(vec_int_.size(), 0);
        EXPECT_EQ(vec_int_.capacity(), 0);

        vec_string_.clear();
        vec_string_.push_back("Cat");
        vec_string_.push_back("Dog");
        vec_string_.resize(1);
        EXPECT_EQ(1, vec_string_.size());
        EXPECT_EQ(1, vec_string_.capacity());
    }

    TEST_F(VectorTest, shrink_to_fit) {
        vec_int_.clear();
        vec_int_.reserve(10);
        vec_int_.push_back(1);
        vec_int_.shrink_to_fit();
        EXPECT_EQ(vec_int_.size(), 1);

        vec_string_.clear();
        vec_string_.push_back("cat");
        vec_string_.shrink_to_fit();
        EXPECT_EQ(vec_string_.size(), 1);

        vec_obj_.clear();
        vec_obj_.shrink_to_fit();
        EXPECT_EQ(vec_obj_.size(), 0);
    }
    
    TEST_F(VectorTest, insert) {
        //insert in beginning of vector, empty vector
   
        vec_int_.clear();
        vec_int_.insert(0, 5);
        EXPECT_EQ(vec_int_.size(), 1);
        EXPECT_EQ(vec_int_[0], 5);
        //insert in beginning of vector, not at max capacity
        vec_int_.clear();
        vec_int_.resize(10);
        vec_int_.push_back(4);
        vec_int_.push_back(6);
        vec_int_.insert(0, 5);
        EXPECT_EQ(vec_int_[0], 5);
        EXPECT_EQ(vec_int_.size(), 3);
        //insert in middle of vector, not at max capacity
        vec_int_.clear();
        vec_int_.shrink_to_fit();
        vec_int_.reserve(5);
        vec_int_.push_back(1);
        vec_int_.push_back(3);
        vec_int_.insert(1, 3);
        EXPECT_EQ(vec_int_[1], 3);
        EXPECT_EQ(vec_int_.at(2), 3);
        EXPECT_EQ(vec_int_.capacity(), 5);
        //insert at end of vector, not at max capacity
        vec_int_.clear();
        vec_int_.shrink_to_fit();
        vec_int_.resize(3);
        vec_int_.push_back(1);
        vec_int_.push_back(2);
        vec_int_.insert(2, 3);
        EXPECT_EQ(vec_int_.at(2), 3);
        EXPECT_EQ(vec_int_.capacity(), 3);
        //insert at beginning, max capcity
        vec_int_.clear();
        vec_int_.shrink_to_fit();
        vec_int_.push_back(1);
        vec_int_.insert(0, 2);
        EXPECT_EQ(vec_int_.size(), 2);
        EXPECT_EQ(vec_int_[0], 2);
        //insert in middle, max capacity
        vec_int_.clear();
        vec_int_.shrink_to_fit();
        vec_int_.reserve(2);
        vec_int_.push_back(1);
        vec_int_.push_back(3);
        vec_int_.insert(1, 2);
        EXPECT_EQ(vec_int_.capacity(), 4);
        EXPECT_EQ(vec_int_.at(1), 2);
        //insert in end, max capacity
        vec_int_.clear();
        vec_int_.shrink_to_fit();
        vec_int_.push_back(1);
        vec_int_.insert(1, 2);
        EXPECT_EQ(vec_int_.size(), 2);
        EXPECT_EQ(vec_int_[1], 2);
    }
    //assign values to vector based in given iterator range
    TEST_F(VectorTest, assign_iter1_iter2) {
        //assign to a vector from size zero 
        vec_int_.clear();
        vec_int_.shrink_to_fit();
        vector::Vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        vec_int_.assign(v1.begin(), v1.end());
        EXPECT_EQ(vec_int_.size(), v1.size());
        EXPECT_EQ(vec_int_.at(0), 1);
        EXPECT_EQ(vec_int_.at(1), 2);
        //assign to a smaller vector from size non-zero 
        vec_int_.push_back(3);
        vector::Vector<int> v2;
        v2.push_back(0);
        vec_int_.assign(v2.begin(), v2.end());
        EXPECT_EQ(vec_int_.size(), v2.size());
        EXPECT_EQ(vec_int_[0], 0);
        //assign to a larger vector from size non-zero
        vec_int_.clear();
        vec_int_.push_back(1);
        vec_int_.assign(v1.begin(), v1.end());
        EXPECT_EQ(vec_int_.size(), v1.size());
        EXPECT_EQ(vec_int_.front(), v1.front());

    }
    //assign n values to the vector
    TEST_F(VectorTest, assign_n_value) {
        //assign to empty vector
        vector::Vector<int> v1;
        v1.assign(10, 1);
        EXPECT_EQ(v1.size(), 10);
        EXPECT_EQ(v1.at(4), 1);
        //assign n values to vector size < n
        vector::Vector<int> v2;
        v2.push_back(3);
        v2.assign(2, 1);
        EXPECT_EQ(v2.size(), 2);
        EXPECT_EQ(v2[0], 1);
        EXPECT_EQ(v2[1], 1);
        //assign n values to vector size > n
        vector::Vector<int> v3;
        v3.push_back(1);
        v3.push_back(2);
        v3.push_back(3);
        v3.assign(2, 0);
        EXPECT_EQ(v3.size(), 2);
        EXPECT_EQ(v3[0], 0);
        EXPECT_EQ(v3[1], 0);
        //assign 0 values to vector size 0
        vector::Vector<int> v4;
        v4.assign(0, 3);
        EXPECT_EQ(v4.size(), 0);
        //assign 0 values to vector size > 0
        vector::Vector<int> v5;
        v5.push_back(1);
        v5.assign(0, 4);
        EXPECT_EQ(v5.empty(), true);
    }

    TEST_F(VectorTest, swap) {
        //swap two emtpy vectors
        vector::Vector<int> v1;
        vector::Vector<int> v2;
        v1.swap(v2);
        EXPECT_EQ(v1.empty(), true);
        EXPECT_EQ(v2.empty(), true);
        //swap one empty vector with non-empty
        v1.push_back(1);
        v1.swap(v2);
        EXPECT_EQ(v1.size(), 0);
        EXPECT_EQ(v2.size(), 1);
        //swap one smaller vector with large one
        
        v1.assign(3, 1);
        v1.swap(v2);
        EXPECT_EQ(v2.size(), 3);
        EXPECT_EQ(v1.size(), 1);
        v1.swap(v2);
        EXPECT_EQ(v2.size(), 1);
        EXPECT_EQ(v1.size(), 3);
    }

    //erase a single index
    TEST_F(VectorTest, erase_single) {
        //erase from beginning of vector
        vector::Vector<int> v1;
        for (int i = 0; i < 10; ++i) {
            v1.push_back(i);
        }
        int* a = v1.erase(v1.begin());
        EXPECT_EQ(v1.size(), 9);
        EXPECT_EQ(*a, 1); 
        EXPECT_EQ(v1.at(0), 1);
        EXPECT_EQ(v1.at(1), 2);
        EXPECT_EQ(v1.at(2), 3);
        EXPECT_EQ(v1.at(3), 4);
        EXPECT_EQ(v1.at(4), 5);
        EXPECT_EQ(v1.at(5), 6);
        EXPECT_EQ(v1.at(6), 7);
        EXPECT_EQ(v1.at(7), 8);
        EXPECT_EQ(v1.at(8), 9);

        //erase in middle of vector
        v1.erase(v1.begin()+1); 
        EXPECT_EQ(v1[0], 1); 
        EXPECT_EQ(v1[1], 3); 
        EXPECT_EQ(v1.size(), 8);
        //erase from end of vector
        int* c = v1.erase(v1.end()-1);
        EXPECT_EQ(v1.size(), 7);
        EXPECT_EQ(v1[6], 8);
    }

    //erase a range from index start to index end
    TEST_F(VectorTest, erase_range) {
        //erase from range size 0
        vector::Vector<int> v1;
        v1.erase(&v1[0], &v1[0]);
        EXPECT_EQ(v1.size(), 0);
        //erase from range beginning
        for (int i = 0; i < 10; ++i) {
            v1.push_back(i);
        }
        int* a = v1.erase(v1.begin(), &v1[5]);
        EXPECT_EQ(*a, 5);
        EXPECT_EQ(v1.size(), 5);
        //erase from range middle
        vector::Vector<int> v2;
        for (int i = 0; i < 10; ++i) {
            v2.push_back(i);
        }
        int* b = v2.erase(&v2[1], &v2[9]);
        EXPECT_EQ(v2[1], 9);
        EXPECT_EQ(v2[0], 0);
        EXPECT_EQ(v2.size(), 2);
        EXPECT_EQ(*b, 9);
        //erase from range end
        vector::Vector<int> v3;
        for (int i = 0; i < 10; ++i) {
            v3.push_back(i);
        }
        int* c = v3.erase(&v3[1], v3.end());
        EXPECT_EQ(v3.size(), 1);
        EXPECT_EQ(v3[0], 0);
        EXPECT_EQ(c, &v3[1]);
        //erase from beginning to end of vector
        vector::Vector<int> v4;
        for (int i = 0; i < 10; ++i) {
            v4.push_back(i);
        }
        int* d = v4.erase(v4.begin(), v4.end());
        EXPECT_EQ(v4.size(), 0);
        EXPECT_EQ(d, &v4[0]);

    }

}
