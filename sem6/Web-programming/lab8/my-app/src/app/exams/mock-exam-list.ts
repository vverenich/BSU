import { Injectable } from '@angular/core';

export interface Exam {
  id?: number | string;
  name: string;
  mark: string;
  enrollee: string;
}
/*
export const Exams: Exam[] = [
  { id: 1, name: 'Math', mark: '10', enrollee: 'Rudnev' },
  { id: 2, name: 'Physics', mark: '9', enrollee: 'Ivanov' },
  { id: 3, name: 'Chemistry', mark: '7', enrollee: 'Petrov' },
  { id: 4, name: 'Biology', mark: '8', enrollee: 'Sidorov' },
  { id: 5, name: 'History', mark: '6', enrollee: 'Smirnov' },
];
*/

// @Injectable({
//   providedIn: 'root'
// })
// export class ExamService {
//   exams: Exam[] = [
//     { id: 1, name: 'Math', mark: '10', enrollee: 'Rudnev' },
//     { id: 2, name: 'Physics', mark: '9', enrollee: 'Ivanov' },
//     { id: 3, name: 'Chemistry', mark: '7', enrollee: 'Petrov' },
//     { id: 4, name: 'Biology', mark: '8', enrollee: 'Sidorov' },
//     { id: 5, name: 'History', mark: '6', enrollee: 'Smirnov' },
//   ];

//   addExam(exam: Exam) {
//     exam.id = this.exams.length + 1;
//     this.exams.push(exam);
//   }
// }
