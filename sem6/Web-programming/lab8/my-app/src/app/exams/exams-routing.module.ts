import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ExamCenterComponent } from './exam-center/exam-center.component';
import { ExamDetailsComponent } from './exam-details/exam-details.component';
import { ExamFormComponent } from './exam-form/exam-form.component';

const examRoutes: Routes = [
  {
    path: '',
    component: ExamCenterComponent,
  },
  {
    path: ':id',
    component: ExamDetailsComponent,
  },
  {
    path: 'new',
    component: ExamFormComponent
  }
];

@NgModule({
  declarations: [],
  imports: [RouterModule.forChild(examRoutes)],
  exports: [RouterModule],
})
export class ExamsRoutingModule {}
