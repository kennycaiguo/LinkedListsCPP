/*******************************************************************************
* File: linkedListTest.cpp
*
* Description: Driver runs all unit tests for our linkedList class 
*
* Author: Alexander DuPree
* 
* Compiler: GNU GCC 5.4.0
*
*******************************************************************************/

#include <iostream>
#include "catch.hpp"
#include "node.hpp"
#include "linkedList.hpp"

TEST_CASE("Constructing Nodes", "[node], [constructors]")
{
    SECTION("Default Construction")
    {
        Node<int> node;

        REQUIRE(*node.Data() == int());
        REQUIRE(node.Next() == nullptr);
    }
    SECTION("Overloaded Construction")
    {
        Node<char> node('n');

        REQUIRE(*node.Data() == 'n');
        REQUIRE(node.Next() == nullptr);
    }
    SECTION("Copy construction")
    {
        Node<int> node1(5);
        Node<int> node2(node1);

        REQUIRE(*node2.Data() == 5);
        REQUIRE(node2.Next() == nullptr);
    }
    
}

TEST_CASE("Using Mutators to manipulate members", "[node], [mutators]")
{
    SECTION("Manipulate data member")
    {
        Node<float> node1;
        Node<char>  node2;
        Node<int>   node3;

        node1.Data(3.545);
        node2.Data('A');
        node3.Data(77);

        REQUIRE(*node1.Data() == float(3.545));
        REQUIRE(*node2.Data() == 'A');
        REQUIRE(*node3.Data() == 77);
    }
    SECTION("Manipulate next Node member")
    {
        Node<int> node1;
        Node<int> node2;

        node1.Next(&node2);

        REQUIRE(node1.Next() == &node2);
    }
}

TEST_CASE("Link Nodes and access linked data members", "[node], [linked]")
{
    SECTION("Traverse a link to access a different Nodes data")
    {
        Node<int> node1(1);
        Node<int> node2(7);

        node1.Next(&node2);

        REQUIRE(*node1.Next()->Data() == 7);
    }
}

TEST_CASE("Constructing Linked Lists instances", "[linkedLists], [constructors]")
{
    SECTION("Default Construction")
    {
        LinkedList<int> list;

        REQUIRE(list.empty() == true);
    }
    SECTION("Fill Construction")
    {
        LinkedList<int> list(4, 100);

        REQUIRE(list.size() == 4);
        for (auto& element : list)
        {
            REQUIRE(element == 100);
        }
    }
    SECTION("Copy construction")
    {
        LinkedList<int> origin(4, 100);
        LinkedList<int> copy(origin);

        REQUIRE(origin == copy);
    }
    SECTION("Copy construction on empty list")
    {
        LinkedList<int> origin;
        LinkedList<int> copy(origin);

        REQUIRE(copy.empty() == true);
    }
}

TEST_CASE("Pushing elements to the front of the list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("Push one element")
    {
        LinkedList<int> list;

        list.push_front(9);

        REQUIRE(*list.begin() == 9);

    }
    SECTION("Push multiple elements")
    {
        LinkedList<char> list;

        list.push_front('A');
        list.push_front('B');
        list.push_front('C');

        REQUIRE(*list.begin() == 'C');
    }
}

TEST_CASE("Pushing elements to the end of the list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("Push one element")
    {
        LinkedList<int> list;

        list.push_back(5);

        REQUIRE(*list.begin() == 5);
        
    }

    SECTION("Push Multiple elements")
    {
        LinkedList<char> list;
        
        list.push_back('X');
        list.push_back('Y');
        list.push_back('Z');

        char character = 'X';
        for (auto& element : list)
        {
            REQUIRE(element == character);
            character++;
        }
    }
}

TEST_CASE("Inserting an element in the list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("Inserting in the middle (at index 2) of a populated list")
    {
        LinkedList<int> list;

        list.push_back(2);
        list.push_back(9);
        list.push_back(6);
        list.push_back(10);
        
        LinkedList<int>::iterator It = list.begin();
        ++It;
        ++It;

        list.insert(It, 5);
        It = list.begin();
        ++It;
        ++It;
        ++It;
       
        REQUIRE(*It == 5);
    }
    SECTION("Inserting at the end of a populated list")
    {
        LinkedList<int> list;

        list.push_back(2);
        list.push_back(9);
        
        LinkedList<int>::iterator It = list.begin();

        ++It;

        list.insert(It, 5);

        ++It;

        REQUIRE(*It == 5);
    }
    SECTION("Inserting at the beginning of a populated list")
    {
        LinkedList<int> list;

        list.push_back(2);
        list.push_back(3); 
        list.push_back(4);

        LinkedList<int>::iterator It = list.begin();

        list.insert(It, 1);

        ++It;

        REQUIRE(*It == 1);
    }
    SECTION("Inserting into an empty list")
    {
        LinkedList<char> list;

        LinkedList<char>::iterator It = list.begin();

        list.insert(It, 'Z');

        REQUIRE(*list.begin() == 'Z');
    }
}

TEST_CASE("Using multiple modifiers on a list", "[linkedLists], [modifiers], [iterators]")
{
    SECTION("push back and push front")
    {
        LinkedList<int> list;

        list.push_back(2);
        list.push_back(3);
        list.push_front(1);

        int i = 1;
        for (auto& it : list)
        {
            REQUIRE(it == i);
            ++i;
        }
    }
}

TEST_CASE("Clearing the list", "[linkedLists], [modifiers]")
{
    SECTION("Clearing a populated list")
    {
        LinkedList<int> list;

        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.clear();
        REQUIRE(list.empty());
    }
    SECTION("Clearing a list with one element")
    {
        LinkedList<int> list;

        list.push_back(1);

        list.clear();
        REQUIRE(list.empty());
    }
    SECTION("Clearing an empty list")
    {
        LinkedList<int> list;

        list.clear();
        REQUIRE(list.empty());
    }
}

TEST_CASE("Using iterators for iteration", "[linkedLists], [iterators]")
{
    SECTION("Standard for loop with prefix increment")
    {
        LinkedList<int> list;

        list.push_front(2);
        list.push_front(1);
        list.push_front(0);

        int i = 0;
        LinkedList<int>::iterator it;

        for (it = list.begin(); it != list.end(); ++it)
        {
            REQUIRE(*it == i);
            ++i;
        }
       
    }
    SECTION("Standard for loop with postfix increment")
    {
        LinkedList<int> list;

        list.push_front(2);
        list.push_front(1);
        list.push_front(0);

        int i = 0;
        LinkedList<int>::iterator it;

        for (it = list.begin(); it != list.end(); it++)
        {
            REQUIRE(*it == i);
            ++i;
        }
    }
    SECTION("Ranged based for loop")
    {
        LinkedList<int> list;

        list.push_front(2);
        list.push_front(1);
        list.push_front(0);

        int i = 0;
        for(auto iter : list)
        {
            REQUIRE(iter == i);
            ++i;
        }
    }
    SECTION("Using const_iterator in standard for loop with prefix increment")
    {
        const LinkedList<int> list(4, 100);

        LinkedList<int>::const_iterator it = list.cbegin();

        for (it = list.cbegin(); it != list.cend(); ++it)
        {
            REQUIRE(*it == 100);
        }
    }
    SECTION("Using const_iterator in standard for loop with postfix increment")
    {
        const LinkedList<int> list(4, 100);

        LinkedList<int>::const_iterator it = list.cbegin();

        for (it = list.cbegin(); it != list.cend(); it++)
        {
            REQUIRE(*it == 100);
        }
    }
/* SEE Issue https://github.com/AlexanderJDupree/LinkedListsCPP/issues/32
    SECTION("Using ranged based for loop on const linkedlist")
    {
        const LinkedList<int> list(5,25);

        for (const auto& element : list)
        {
            REQUIRE(element == 25);
        }
    }
*/
}

TEST_CASE("Test size() function", "[linkedLists], [size], [capacity]")
{
    SECTION("Empty linked list")
    {
        LinkedList<int> list;

        REQUIRE(list.size() == 0);
    }
    SECTION("A populated linked list")
    {
        LinkedList<char> list;

        list.push_front('A');
        list.push_front('B');
        list.push_front('C');

        REQUIRE(list.size() == 3);
    }
   
}

TEST_CASE("Test comparison operators", "[linkedLists], [comparison], [operators]")
{
    SECTION("Two identical linked lists")
    {
        LinkedList<int> left(5, 20);
        LinkedList<int> right(5, 20);

        REQUIRE(left == right);
    }
    SECTION("Two different linked lists")
    {
        LinkedList<int> left(5, 20);
        LinkedList<int> right;

        REQUIRE(left != right);
    }
}

