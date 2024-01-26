/***************************************************************************
 * ROM Properties Page shell extension. (gtk/tests)                        *
 * SortFuncsTest.cpp: sort_funcs.c test.                                   *
 *                                                                         *
 * Copyright (c) 2016-2024 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

// Google Test
#include "gtest/gtest.h"
#include "tcharx.h"

// GTK
#include "gtk-compat.h"

// sort_funcs.h
#include "sort_funcs.h"

// for ARRAY_SIZE()
#include "common.h"

// C includes (C++ namespace)
#include <cstdio>

// C++ STL classes
using std::string;
using std::vector;

namespace LibRomData { namespace Tests {

class ListDataSortProxyModelTest : public ::testing::Test
{
	protected:
		ListDataSortProxyModelTest()
			: listStore(nullptr)
			, sortProxy(nullptr)
		{ }

		~ListDataSortProxyModelTest() override
		{
			g_clear_object(&sortProxy);
			g_clear_object(&listStore);
		}

	public:
		void SetUp() override;
		void TearDown() override;

	protected:
		GtkListStore *listStore;	// List data
		GtkTreeModel *sortProxy;	// Sort proxy

	public:
		// Sorted strings
		static const char *const sorted_strings_asc[4][24];
};

// Sorted strings
const char *const ListDataSortProxyModelTest::sorted_strings_asc[4][24] = {
	// Column 0: Greek alphabet, standard sort
	{"Alpha", "Epsilon", "Eta", "Gamma",
	 "Iota", "Lambda", "Nu", "Omicron",
	 "Phi", "Psi", "Rho", "Tau",
	 "bEta", "cHi", "dElta", "kAppa",
	 "mU", "oMega", "pI", "sIgma",
	 "tHeta", "uPsilon", "xI", "zEta"},
	// Column 1: Greek alphabet, case-insensitive sort
	{"Alpha", "bEta", "cHi", "dElta",
	 "Epsilon", "Eta", "Gamma", "Iota",
	 "kAppa", "Lambda", "mU", "Nu",
	 "oMega", "Omicron", "Phi", "pI",
	 "Psi", "Rho", "sIgma", "Tau",
	 "tHeta", "uPsilon", "xI", "zEta"},
	// Column 2: Numbers, standard sort
	{"1", "10", "11", "12",
	 "13", "14", "15", "16",
	 "17", "18", "19", "2",
	 "20", "21", "22", "23",
	 "24", "3", "4", "5",
	 "6", "7", "8", "9"},
	// Column 3: Numbers, numeric sort
	{"1", "2", "3", "4",
	 "5", "6", "7", "8",
	 "9", "10", "11", "12",
	 "13", "14", "15", "16",
	 "17", "18", "19", "20",
	 "21", "22", "23", "24"}
};

void ListDataSortProxyModelTest::SetUp()
{
	// Create the GtkListStore and sort proxy tree models.
	listStore = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	sortProxy = gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(listStore));

	// Add the list data.
	// NOTE: Outer vector is rows, not columns!
	// TODO: Add from the sorted data, then do a random sort?
	static const char *const list_data_randomized[][4] = {
		{"pI", "tHeta", "2", "7"},
		{"cHi", "Iota", "15", "1"},
		{"uPsilon", "Alpha", "1", "22"},
		{"Psi", "mU", "14", "15"},
		{"xI", "Nu", "20", "16"},
		{"Gamma", "Phi", "17", "12"},
		{"Epsilon", "Rho", "11", "23"},
		{"zEta", "pI", "5", "8"},
		{"Lambda", "Eta", "8", "5"},
		{"Nu", "bEta", "18", "19"},
		{"Iota", "Tau", "10", "13"},
		{"Eta", "Lambda", "13", "20"},
		{"kAppa", "Psi", "23", "9"},
		{"Omicron", "Gamma", "4", "18"},
		{"tHeta", "sIgma", "7", "4"},
		{"dElta", "zEta", "3", "21"},
		{"sIgma", "Omicron", "21", "14"},
		{"mU", "oMega", "6", "24"},
		{"bEta", "Epsilon", "24", "11"},
		{"oMega", "cHi", "16", "6"},
		{"Tau", "xI", "19", "17"},
		{"Alpha", "uPsilon", "22", "2"},
		{"Phi", "dElta", "12", "10"},
		{"Rho", "kAppa", "9", "3"}
	};

	for (auto *p : list_data_randomized) {
		GtkTreeIter treeIter;
		gtk_list_store_append(listStore, &treeIter);
		gtk_list_store_set(listStore, &treeIter, 0, p[0], 1, p[1], 2, p[2], 3, p[3], -1);
	}

	// Sorting order (function pointers)
	static const GtkTreeIterCompareFunc sort_funcs[4] = {
		// Column 0: Greek alphabet, standard sort
		sort_RFT_LISTDATA_standard,
		// Column 1: Greek alphabet, case-insensitive sort
		sort_RFT_LISTDATA_nocase,
		// Column 2: Numbers, standard sort
		sort_RFT_LISTDATA_standard,
		// Column 3: Numbers, numeric sort
		sort_RFT_LISTDATA_numeric,
	};

	// Set the column sort functions.
	for (gint col = 0; col < 4; col++) {
		gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(sortProxy),
			col, sort_funcs[col], GINT_TO_POINTER(col), nullptr);
	}
}

void ListDataSortProxyModelTest::TearDown()
{
	g_clear_object(&sortProxy);
	g_clear_object(&listStore);
}

/**
 * Test sorting each column in ascending order.
 */
TEST_F(ListDataSortProxyModelTest, ascendingSort)
{
	static const int columnCount = 4;
	const int rowCount = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(listStore), nullptr);
	ASSERT_GT(rowCount, 0) << "No rows available???";

	for (int col = 0; col < columnCount; col++) {
		gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(sortProxy), col, GTK_SORT_ASCENDING);
		int row = 0;

		GtkTreeIter iter;
		gboolean ok = gtk_tree_model_get_iter_first(sortProxy, &iter);
		ASSERT_TRUE(ok);
		do {
			gchar *str = nullptr;
			gtk_tree_model_get(sortProxy, &iter, col, &str, -1);
			EXPECT_NE(str, nullptr) << "Unexpected NULL pointer";
			if (str) {
				EXPECT_NE(str[0], '\0') << "Unexpected empty string";
				EXPECT_STREQ(sorted_strings_asc[col][row], str) << "sorting column " << col << ", checking row " << row;
				g_free(str);
			}

			// Next row.
			row++;
			ok = gtk_tree_model_iter_next(sortProxy, &iter);
		} while (ok);

		ASSERT_EQ(rowCount, row) << "Row count does not match the number of rows received";
	}
}

/**
 * Test sorting each column in descending order.
 */
TEST_F(ListDataSortProxyModelTest, descendingSort)
{
	static const int columnCount = 4;
	const int rowCount = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(listStore), nullptr);
	ASSERT_GT(rowCount, 0) << "No rows available???";

	for (int col = 0; col < columnCount; col++) {
		gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(sortProxy), col, GTK_SORT_DESCENDING);
		int row = 0;

		GtkTreeIter iter;
		gboolean ok = gtk_tree_model_get_iter_first(sortProxy, &iter);
		ASSERT_TRUE(ok);
		do {
			gchar *str = nullptr;
			gtk_tree_model_get(sortProxy, &iter, col, &str, -1);
			EXPECT_NE(str, nullptr) << "Unexpected NULL pointer";
			if (str) {
				EXPECT_NE(str[0], '\0') << "Unexpected empty string";

				const int drow = ARRAY_SIZE(sorted_strings_asc[row]) - row - 1;
				EXPECT_STREQ(sorted_strings_asc[col][drow], str) << "sorting column " << col << ", checking row " << row;
				g_free(str);
			}

			// Next row.
			row++;
			ok = gtk_tree_model_iter_next(sortProxy, &iter);
		} while (ok);

		ASSERT_EQ(rowCount, row) << "Row count does not match the number of rows received";
	}
}

} }

/**
 * Test suite main function.
 */
extern "C" int gtest_main(int argc, TCHAR *argv[])
{
	fprintf(stderr, "GTK%d UI frontend test suite: ListDataSortProxyModel tests.\n\n", GTK_MAJOR_VERSION);
	fflush(nullptr);

	// coverity[fun_call_w_exception]: uncaught exceptions cause nonzero exit anyway, so don't warn.
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
