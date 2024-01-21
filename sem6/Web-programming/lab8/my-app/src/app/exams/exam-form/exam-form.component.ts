
import { Component } from '@angular/core';
import { Exam } from '../mock-exam-list';
import { ExamsService } from '../services/exams.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-exam-form',
  templateUrl: './exam-form.component.html'
})

export class ExamFormComponent {
  exam: Exam = {
    name: '',
    mark: '',
    enrollee: ''
  };

  constructor(
    private examService: ExamsService,
    private router: Router
  ) {}

  onSubmit() {
    this.examService.save(this.exam)
      .subscribe(_ => {
        this.router.navigateByUrl('/');
      });
  }
}
