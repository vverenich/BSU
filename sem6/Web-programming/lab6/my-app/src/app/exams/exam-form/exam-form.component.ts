
import { FormsModule }   from '@angular/forms';
import { Component } from '@angular/core';
import { NgModule } from '@angular/core';
import { Exam, ExamService } from '../mock-exam-list';

/*
@NgModule({
  imports: [
             FormsModule,      //<----------make sure you have added this.
           ],
})
*/

@Component({
  selector: 'app-exam-form',
  templateUrl: './exam-form.component.html'
})

export class ExamFormComponent {
  exam: Exam = new Exam();

  constructor(private examService: ExamService) {}

  onSubmit() {
    console.log(this.exam);
    this.examService.addExam(this.exam);
    this.exam = new Exam();
  }
}