import { Component, OnInit } from '@angular/core';

import { Observable } from 'rxjs';
import { Exam } from '../mock-exam-list';
import { ExamsService } from '../services/exams.service';

@Component({
  selector: 'app-exam-list',
  templateUrl: './exam-list.component.html',
  styleUrls: ['./exam-list.component.css']
})
export class ExamListComponent implements OnInit {
  exams$: Observable<Exam[]>;

  constructor(private examService: ExamsService) { console.log("dsfa") }

  ngOnInit(): void {
    this.exams$ = this.examService.getExams();
    this.exams$.subscribe(exams => console.log(exams));
  }
}
