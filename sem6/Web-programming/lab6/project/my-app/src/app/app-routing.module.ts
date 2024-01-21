import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ExamCenterComponent } from './exams/exam-center/exam-center.component';
import { ExamListComponent } from './exams/exam-list/exam-list.component';
import { ExamDetailsComponent } from './exams/exam-details/exam-details.component';
import { ExamFormComponent } from './exams/exam-form/exam-form.component';

const routes: Routes = [
  {
    path: '',
    component: ExamCenterComponent,
    children: [
      {
        path: '',
        component: ExamListComponent
      },
      {
        path: 'exam-details/:id',
        component: ExamDetailsComponent
      }
    ]
  },
  {
    path: 'exam-form',
    component: ExamFormComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
