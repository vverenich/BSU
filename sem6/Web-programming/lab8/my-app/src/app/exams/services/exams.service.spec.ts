import { TestBed } from '@angular/core/testing';

import { ExamsService } from './exams.service';

describe('ExamsService', () => {
  let service: ExamsService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(ExamsService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
