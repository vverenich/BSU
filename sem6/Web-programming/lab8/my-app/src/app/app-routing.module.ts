import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ExamCenterComponent } from './exams/exam-center/exam-center.component';
import { ExamDetailsComponent } from './exams/exam-details/exam-details.component';
import { ExamFormComponent } from './exams/exam-form/exam-form.component';

const routes: Routes = [
  {
    path: '',
    component: ExamCenterComponent,
  },
  {
    path: 'new',
    component: ExamFormComponent
  },
  {
    path: ':id',
    component: ExamDetailsComponent
  },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
