import { Component } from '@angular/core';

import { Bike } from './bike';

export const BIKES: Bike[] = [
  { id: 1, model: 'CBR250R', manufacturer: 'Honda' },
  { id: 2, model: 'CBR150R', manufacturer: 'Honda' },
  { id: 3, model: 'Ninja250R', manufacturer: 'Kawasaki' },
  { id: 4, model: 'CBR1000R', manufacturer: 'Honda' },
  { id: 5, model: 'Ninja1000RR', manufacturer: 'Kawasaki' }
];


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'DemoAngular2';
   bikes = BIKES;
  selectedBike: Bike;
  onSelect(bike: Bike): void {
    this.selectedBike = bike;
  }
}
