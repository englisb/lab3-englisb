#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"
#include "Questions.h"
    


   
    
//=========Question 1==================================
	void TestQ1_two_strings(CuTest *tc) {
		
		CuAssertStrEquals(tc, "HelloWorld!", my_strcat("Hello","World!"));
	}
    
	void TestQ1_second_empty(CuTest *tc) {
		
		CuAssertStrEquals(tc, "Hello", my_strcat("Hello",""));
	}
	void TestQ1_first_empty(CuTest *tc) {
		
		CuAssertStrEquals(tc, "World!", my_strcat("","World!"));
	}
    
	void TestQ1_both_empty(CuTest *tc) {

			CuAssertStrEquals(tc, "", my_strcat("",""));
		}

//===========================================================
//=================Question 2================================
	void TestQ2_find_notThere(CuTest *tc) {

		char inputFile[] =  "students.txt";
		int size;
		//create list using the input file
		student **Clist = create_class_list(inputFile,&size);

		int expected = -1;
		int actual = find(0011,Clist,size);

		CuAssertIntEquals(tc, expected, actual);

	}

	void TestQ2_find_There(CuTest *tc) {

		char inputFile[] =  "students.txt";
		int size;
		//create list using the input file
		student **Clist = create_class_list(inputFile,&size);

		int expected = 4;
		int actual = find(9000,Clist,size);

		CuAssertIntEquals(tc, expected, actual);

	}

	void TestQ2_inputGradesAndCalculateFinal(CuTest *tc) {



		char inputFile[] =  "students.txt";
		char gradesFile[] =  "grades.txt";
		int size;
		//create list using the input file
		student **Clist = create_class_list(inputFile,&size);
		//input grades using the grades input file
		input_grades(gradesFile,Clist,size);
		//calculate final grades
		compute_final_course_grades(Clist,size);
		//Output final course marks
		output_final_course_grades("outputGrades.txt",Clist,size);

		//now we open the golden file with the written file and compare line by line

		char actualFile[] =  "outputGrades.txt";
		char goldenFile[] =  "output.txt";

		char actual[1000], expected[1000];
		int actualID,expectedID;
		double actualFinalGrade,expectedFinalGrade;
		FILE *actualPtr, *expectedPtr;
		if ((actualPtr = fopen(actualFile, "r")) == NULL || (expectedPtr = fopen(goldenFile, "r")) == NULL) {
			printf("Error! opening file");
			// Program exits if file pointer returns NULL.
			exit(1);
		}

		int actualNumStudents,expectedNumStudents;


		fscanf(actualPtr,"%d",&actualNumStudents);

		fscanf(expectedPtr,"%d",&expectedNumStudents);

		CuAssertIntEquals(tc, expectedNumStudents, actualNumStudents);

		int i;
		for(i=0;i<expectedNumStudents;i++){
		//while (actualPtr != NULL && expectedPtr!=NULL){
			// reads text until newline is encountered
		/*	fscanf(actualPtr, "%[^\n]", actual);
			printf("%s ", actual);
			fscanf(expectedPtr, "%[^\n]", expected);
			printf("%s\n", expected);

			CuAssertStrEquals(tc, expected, actual);

		*/
			fscanf(actualPtr,"%d",&actualID);

			fscanf(expectedPtr,"%d",&expectedID);

			CuAssertIntEquals(tc, expectedID, actualID);

			fscanf(actualPtr,"%lf",&actualFinalGrade);
			fscanf(expectedPtr,"%lf",&expectedFinalGrade);
			CuAssertDblEquals(tc, expectedFinalGrade, actualFinalGrade,0.000001);
		}
		if ((actualPtr == NULL && expectedPtr!=NULL)|| (actualPtr != NULL && expectedPtr==NULL)){

			printf("files are not of equal size");
			// Program exits if file pointer returns NULL.
			exit(1);

		}

	}

	void TestQ2_megaTest(CuTest *tc) {
		char inputFile[] =  "testcase_students.txt";
		char gradesFile[] =  "testcase_grades.txt";
		int size;
		//create list using the input file
		student **class_list = create_class_list(inputFile,&size);
		//input grades using the grades input file
		input_grades(gradesFile,class_list,size);
		//calculate final grades
		compute_final_course_grades(class_list,size);
		//Output final course marks
		output_final_course_grades("outputGrades.txt",class_list,size);

		//now we open the golden file with the written file and compare line by line

		char actualFile[] =  "outputGrades.txt";
		char goldenFile[] =  "testcase_expected_output.txt";

		int actualID,expectedID;
		double actualFinalGrade,expectedFinalGrade;
		FILE *actualPtr, *expectedPtr;
		if ((actualPtr = fopen(actualFile, "r")) == NULL || (expectedPtr = fopen(goldenFile, "r")) == NULL) {
			printf("Error! opening file");
			// Program exits if file pointer returns NULL.
			exit(1);
		}

		int actualNumStudents,expectedNumStudents;


		fscanf(actualPtr,"%d",&actualNumStudents);

		fscanf(expectedPtr,"%d",&expectedNumStudents);

		CuAssertIntEquals(tc, expectedNumStudents, actualNumStudents);

		int i;
		for(i=0;i<expectedNumStudents;i++){
		//while (actualPtr != NULL && expectedPtr!=NULL){

			fscanf(actualPtr,"%d",&actualID);

			fscanf(expectedPtr,"%d",&expectedID);

			CuAssertIntEquals(tc, expectedID, actualID);

			fscanf(actualPtr,"%lf",&actualFinalGrade);
			fscanf(expectedPtr,"%lf",&expectedFinalGrade);
			CuAssertDblEquals(tc, expectedFinalGrade, actualFinalGrade,0.000001);
		}
		if ((actualPtr == NULL && expectedPtr!=NULL)|| (actualPtr != NULL && expectedPtr==NULL)){

			printf("files are not of equal size");
			// Program exits if file pointer returns NULL.
			exit(1);

		}

		//student IDs for the three trials of withdraw()
		int studNotThere = 3000, studThere1 = 3500, studThere2 = 2014;
		//create a copy of class_list at a different memory location
		student **class_copy = create_class_list(inputFile,&size);

		input_grades(gradesFile,class_copy,size);
		compute_final_course_grades(class_copy,size);

		printf("WITHDRAWING STUDENT #%d\n", studNotThere);
		withdraw(studNotThere, class_copy, &size);

		//check if withdraw() has failed; if the original and copy class list have identical student positions
		for(i = 0; i < size; i++){
			CuAssertIntEquals(tc, class_list[i]->student_id, class_copy[i]->student_id);
		}

		int expected1[] = {1243, 2014, 2333, 6666};

		printf("WITHDRAWING STUDENT #%d\n", studThere1);
		withdraw(studThere1, class_copy, &size);

		int new_size = size - 1;

		for(i = 0; i < new_size; i++){
			CuAssertIntEquals(tc, class_copy[i]->student_id, expected1[i]);
		}


		int expected2[] = {1243, 2333, 6666};

		printf("WITHDRAWING STUDENT #%d\n", studThere2);
		withdraw(studThere2, class_copy, &new_size);

		new_size -= 1;

		for(i = 0; i < new_size; i++){
			CuAssertIntEquals(tc, class_copy[i]->student_id, expected2[i]);
		}


		destroy_list(class_copy, &new_size);
		CuAssertIntEquals(tc, 0, new_size);


	}

//===========================================================
//=================Question 3================================
//	void TestQ3_readandSort1(CuTest *tc) {
//
//		char inputFile[] =  "wordlist.txt";
//		int size;
//		//create list using the input file
//		char **actualList = read_words(inputFile,&size);
//		sort_words(actualList,size);
//
//		char *expectedList[]={"apple","banana","hello","milan","programming","zebra"};
//
//		int i;
//		for (i=0;i<size;i++)
//			CuAssertStrEquals(tc, expectedList[i], actualList[i]);
//
//	}
//
//	void TestQ3_readandSort2(CuTest *tc) {
//
//		char inputFile[] =  "wordlist.txt";
//		int size;
//		//create list using the input file
//		char **actualList = read_words(inputFile,&size);
//		sort2_words(actualList,size);
//
//		char *expectedList[]={"apple","banana","hello","milan","programming","zebra"};
//
//
//
//		int i;
//		for (i=0;i<size;i++)
//			CuAssertStrEquals(tc, expectedList[i], actualList[i]);
//
//	}

    
  
//===========================================================
	CuSuite* Lab3GetSuite() {
		CuSuite* suite = CuSuiteNew();
		SUITE_ADD_TEST(suite, TestQ1_two_strings); 
		SUITE_ADD_TEST(suite, TestQ1_second_empty);
		SUITE_ADD_TEST(suite, TestQ1_first_empty);
		SUITE_ADD_TEST(suite, TestQ1_both_empty);

		SUITE_ADD_TEST(suite, TestQ2_find_notThere);
		SUITE_ADD_TEST(suite, TestQ2_find_There);
		SUITE_ADD_TEST(suite, TestQ2_inputGradesAndCalculateFinal);
		SUITE_ADD_TEST(suite, TestQ2_megaTest);

		/*
		SUITE_ADD_TEST(suite, TestQ3_readandSort1);
		SUITE_ADD_TEST(suite, TestQ3_readandSort2);
        
*/

		return suite;
	}
    
