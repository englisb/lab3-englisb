#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"



student **create_class_list(char *filename, int *sizePtr){

	student **class_list;


	/*write your implementation here*/

	int i;

	FILE *studFile = fopen(filename, "r");		//open the passed file in read mode
	fscanf(studFile,"%d", sizePtr);				//scan the file for the first int and insert it into the size ptr

	class_list = (student**)malloc(*sizePtr * sizeof(student*));	//create the double pointer class_list which is an array of memory slots for the size of student ponters


	for(i = 0; i < *sizePtr; i++){
		class_list[i] = (student*) calloc(1, sizeof(student));
		fscanf(studFile,"%d%s%s", &(class_list[i]->student_id), class_list[i]->first_name, class_list[i]->last_name);
	//scan the file 3 times for student id, first name, then last name and assign them to a reserved memory slot in the class list
	//do this for each student
	}

	fclose(studFile);
	//close the file

	/* finally return the created class list*/
	return class_list;
}

int find(int idNo, student **list, int size)
{
	int listPos;

	for(listPos = 0; listPos < size; listPos++){
		if(idNo == (list[listPos]->student_id)){	//check if idNo is the same as the student's id for each student in the list
			return listPos;
		}
	}


	return -1;		//if the student isn't there return -1
}

void input_grades(char *filename, student **list, int size)
{
	/*write your implementation here*/

	FILE *gradeFile = fopen(filename, "r");

	int classListPos, fileStudID, i;

	for(i = 0; i < size; i++){
		fscanf(gradeFile,"%d", &fileStudID);			//scans student id from the grade file
		classListPos = find(fileStudID, list, size);	//finds the position in the list of student that has said id
		fscanf(gradeFile,"%d", &(list[classListPos]->project1_grade));	//scans the proj1 and proj2 grade and assigns it to the student
		fscanf(gradeFile,"%d", &(list[classListPos]->project2_grade));
	}
	//loops as many times as there are students

	fclose(gradeFile);
}

void compute_final_course_grades(student **list, int size)
{

	/*write your implementation here*/
	int listPos;

	for(listPos = 0; listPos < size; listPos++){
		list[listPos]->final_grade = (list[listPos]->project1_grade + list[listPos]->project2_grade) / 2.0;
	}	//averages the project grades of the student and assigns it to the final grade of the student
	//performs this for every student
}

void output_final_course_grades(char *filename, student **list, int size)
{
	FILE *gradeFile = fopen(filename, "w");
	int listPos;

	fprintf(gradeFile, "%d\n", size);	//first print the size into the file

	for(listPos = 0; listPos < size; listPos++){
		fprintf(gradeFile, "%d %f\n", list[listPos]->student_id, list[listPos]->final_grade);
	}	//print the student number then final grade for each subsequent student all separated by whitespace

	fclose(gradeFile);
}


void withdraw(int idNo, student **list, int* sizePtr)
{
	/*write your implementation here*/
	int i, listPos;

	listPos = find(idNo, list, *sizePtr);


	if(listPos != -1){
		free(list[listPos]);		//deallocate the memory of the student to be eliminated

		//from the slot of the eliminated student, shift contents of all slots to the right by 1 up to the last slot
		for(i = listPos; i < *sizePtr - 1; i++){
			list[i] = list[i + 1];
		}

		list = realloc(list, *sizePtr - 1);		//resize list to account for the cloned slot at the end
	}

	else{
		printf("Error! Student does not exist.\n");
	}


}

void destroy_list(student **list, int *sizePtr)
{
	int i;
	for(i = 0; i < *sizePtr; i++){		//free every memory slot allocated for a student in list
		free(list[i]);
	}

	*sizePtr = 0;

}
