import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Exam } from '../mock-exam-list';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root',
})
export class ExamsService {
  examUrl = 'http://localhost:8080/results';

  constructor(private _httpClient: HttpClient) { }

  getExams(): Observable<Exam[]> {
    return this._httpClient.get<Exam[]>(this.examUrl);
  }

  getExam(id: string | number | null): Observable<Exam> {
    return this._httpClient.get<Exam>(`${this.examUrl}/${id}`)
  }

  save(exam: Exam): Observable<any> {
    return this._httpClient.post(this.examUrl, exam);
  }

  delete(id: string | number | null): Observable<any> {
    return this._httpClient.delete(`${this.examUrl}/${id}`);
  }
}
