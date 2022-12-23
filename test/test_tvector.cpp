#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int arr[] = { 2, 1, 15 };
	TDynamicVector<int> v(arr, 3);
	TDynamicVector<int> v1(v);
	EXPECT_EQ(1, v == v1);
	//double arr[] = { 10.0, -2.0, 3.0, 4.0 };
	//size_t size = 4;
	//TDynamicVector<double> v(arr, size);
	//TDynamicVector<double> copy(v);
	//EXPECT_TRUE(v == copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10), v2;
	v2 = v1;
	EXPECT_NE(&v1[0], &v2[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{

	ASSERT_ANY_THROW(TDynamicVector<int> v(-4));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(10);
  EXPECT_ANY_THROW(v.at(11));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(3), v1(3);
	for (int i = 0; i < 3; i++) {
		v[i] = 0;
		v1[i] = i;
	}
	v = v1;
  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(2, v[2]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(10), v1(12);
	v = v1;
  EXPECT_EQ(12, v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(3), v1(5);
  ASSERT_NO_THROW(v = v1);

}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(10), v1(10);
  EXPECT_EQ(1, v == v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(10);
	EXPECT_EQ(1, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(10), v1(12);
	EXPECT_EQ(1, v != v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	for (int i = 0; i < 3; i++)
		v[i] = i;
	int sc = 3;
	v = v + sc;

	EXPECT_EQ(3, v[0]);
	EXPECT_EQ(4, v[1]);
	EXPECT_EQ(5, v[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
  for (int i = 0; i < 3; i++)
	  v[i] = i+4;
  int sc = 3;
  v = v - sc;

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	for (int i = 0; i < 3; i++)
		v[i] = i;
	int sc = 3;
	v = v * sc;

	EXPECT_EQ(0, v[0]);
	EXPECT_EQ(3, v[1]);
	EXPECT_EQ(6, v[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(3), v1(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
		v1[i] = i + 1;
	}
	v = v + v1;

	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(3, v[1]);
	EXPECT_EQ(5, v[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v1(5);

	EXPECT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(3), v1(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
		v1[i] = i + 1;
	}
	v = v1 - v;

	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(1, v[1]);
	EXPECT_EQ(1, v[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v1(5);

	EXPECT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{

	TDynamicVector<int> v(2), v1(2);
	v[0] = 2;
	v[1] = 2;
	v1[0] = 3;
	v1[1] = 3;
	int tmp = 12;
	EXPECT_EQ(tmp, v * v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v1(5);
	ASSERT_ANY_THROW(v * v1);
}

