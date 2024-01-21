import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule, Routes } from '@angular/router';
import { ExamCenterComponent } from './exam-center/exam-center.component';
import { ExamListComponent } from './exam-list/exam-list.component';
import { ExamDetailsComponent } from './exam-details/exam-details.component';
import { ExamsRoutingModule } from './exams-routing.module';
import { ExamFormComponent } from './exam-form/exam-form.component';

const examRoutes: Routes = [
  { path: '', redirectTo: 'exam-center', pathMatch: 'full' },
  { path: 'exam-center', component: ExamCenterComponent, children: [
    { path: '', component: ExamListComponent },
    { path: ':id', component: ExamDetailsComponent }
  ]}
];

@NgModule({
  declarations: [
    ExamCenterComponent,
    ExamListComponent,
    ExamDetailsComponent,
  ],
  imports: [
    CommonModule,
    ExamsRoutingModule,
    RouterModule.forChild(examRoutes)
  ]
})
export class ExamsModule { }
