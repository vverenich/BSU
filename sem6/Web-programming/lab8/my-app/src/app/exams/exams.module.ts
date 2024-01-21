import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule, Routes } from '@angular/router';
import { ExamCenterComponent } from './exam-center/exam-center.component';
import { ExamListComponent } from './exam-list/exam-list.component';
import { ExamDetailsComponent } from './exam-details/exam-details.component';
import { ExamsRoutingModule } from './exams-routing.module';
import { ExamFormComponent } from './exam-form/exam-form.component';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';


@NgModule({
  declarations: [
    ExamCenterComponent,
    ExamListComponent,
    ExamDetailsComponent,
    ExamFormComponent
  ],
  imports: [
    CommonModule,
    ExamsRoutingModule,
    HttpClientModule,
    FormsModule
    // RouterModule.forChild(examRoutes)
  ]
})
export class ExamsModule { }
