import { Component, OnInit } from '@angular/core';

import { ExamService } from '../mock-exam-list';

@Component({
  selector: 'app-exam-list',
  templateUrl: './exam-list.component.html',
  styleUrls: ['./exam-list.component.css']
})
export class ExamListComponent implements OnInit {
  exams = this.examService.exams;

  constructor(private examService: ExamService) { }

  ngOnInit(): void {
  }
}
