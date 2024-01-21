const dom = (function () {

  let formId = "";

  const payReceiptForm = {
    receiptId: {
      label: "Receipt ID",
      type: "number",
      class: "form-control",
      placeholder: "Enter receipt ID",
      name: "receiptId",
      id: "receiptId-input",
    },
    submitButton: {
      type: "submit",
      class: "btn",
      value: "Pay",
    }
  };

  const typeRoomsForm = {
    typeIdRoom: {
        label: 'Type',
        value: '',
        type: 'text',
        class: 'form-control',
        placeholder: 'Enter type room',
        name: 'typeIdRoom',
        id: 'typeIdRoom',
    },
    arrivalDateRoom: {
      label: 'Arrival date',
      type: 'date',
      class: 'form-control',
      name: 'arrivalDate-room',
      id: 'arrivalDate-room',
    },
    departureDateRoom: {
      label: 'Departure date',
      type: 'date',
      class: 'form-control',
      name: 'departureDate-room',
      id: 'departureDate-room',
    },
    submitButton: {
        type: 'submit',
        class: 'btn',
        value: 'Show'
    }
};

const confirmBookingForm = {
  bookingId: {
    label: "Booking ID",
    type: "number",
    class: "form-control",
    placeholder: "Enter booking ID",
    name: "bookingId",
    id: "bookingId-input",
  },
  submitButton: {
      type: 'submit',
      class: 'btn',
      value: 'Confirm'
  }
};

const confirmBookingRoomForm = {
    confirmRoomId: {
      label: "Room ID",
      type: "number",
      class: "form-control",
      placeholder: "Enter room ID",
      name: "confirmRoomId",
      id: "confirmRoomId-input",
    },
    submitButton: {
      type: 'submit',
      class: 'btn',
      value: 'Confirm'
    }
  };


const createBookingForm = {
  typeId: {
      label: 'Type',
      value: '',
      type: 'text',
      class: 'form-control',
      placeholder: 'Enter type room',
      name: 'typeId',
      id: 'typeId-input',
  },
  guestsNum: {
    label: "Guests",
    type: "number",
    class: "form-control",
    placeholder: "Enter number of guests",
    name: "guestsNum",
    id: "guestsNum-input",
  },
  arrivalDate: {
    label: 'Arrival date',
    type: 'date',
    class: 'form-control',
    name: 'arrivalDate',
    id: 'arrivalDate',
  },
  departureDate: {
    label: 'Departure date',
    type: 'date',
    class: 'form-control',
    name: 'departureDate',
    id: 'departureDate',
  },
  submitButton: {
      type: 'submit',
      class: 'btn',
      value: 'Create'
  }
};

  function buildForm(form, type) {
    var array;
    switch (type) {
      case "payReceiptForm":
        array = payReceiptForm;
        break;
        
        case 'typeRoomsForm':
          array = typeRoomsForm;
          break;

        case 'confirmBookingForm':
          array = confirmBookingForm;
          break;

      case 'confirmBookingRoomForm':
        array = confirmBookingRoomForm;
        break;

        case 'createBookingForm':
          array = createBookingForm;
          break;
    }

    
  function onSubmit() {
  }


    for (const prop in array) {
      if (array[prop].type === "submit") {
        const submit = document.createElement("input");
        submit.setAttribute("type", array[prop].type);
        submit.setAttribute("class", array[prop].class);
        submit.value = array[prop].value;
        form.appendChild(submit);
        form.onSubmit = onSubmit;
      } else {
        const formDiv = document.createElement("div");
        formDiv.setAttribute("class", "form-group");
        const label = document.createElement("label");
        label.innerHTML = array[prop].label;
        formDiv.appendChild(label);
        const input = document.createElement("input");
        input.setAttribute("type", array[prop].type);
        input.setAttribute("class", array[prop].class);
        input.setAttribute("value", array[prop].value);
        input.setAttribute("placeholder", array[prop].placeholder);
        input.setAttribute("name", array[prop].name);
        input.setAttribute("id", array[prop].id);
        input.required = true;
        formDiv.appendChild(input);
        form.appendChild(formDiv);
      }
    }
  }

  function initPage() {
   
    const payReceiptForm = document.getElementById("pay-receipts-form");
    if (payReceiptForm != null) {
      buildForm(payReceiptForm, "payReceiptForm");
      formId = "pay-receipts-form";
      return;
    }
    
    const typeRoomsForm = document.getElementById("type-rooms-form");
    if (typeRoomsForm != null) {
      buildForm(typeRoomsForm, "typeRoomsForm");
      formId = "type-rooms-form";
      return;
    }

    const confirmBookingForm = document.getElementById("confirm-booking-form");
    if (confirmBookingForm != null) {
      buildForm(confirmBookingForm, "confirmBookingForm");
      formId = "confirm-booking-form";
      return;
    }

    const confirmBookingRoomForm = document.getElementById("confirm-booking-room-form");
    if (confirmBookingRoomForm != null) {
      buildForm(confirmBookingRoomForm, "confirmBookingRoomForm");
      formId = "confirm-booking-room-form";
      return;
    }
    const createBookingForm = document.getElementById("create-booking-form");
    if (createBookingForm != null) {
      buildForm(createBookingForm, "createBookingForm");
      formId = "create-booking-form";
      return;
    }
  }

  return { initPage };
})();

dom.initPage();

$(document).ready(function() {
  $("#pay-receipts-form").validate({
    validClass: "valid success-handle",
    rules: {
      receiptId: {
        required: true,
        number: true,
        min: 1
      }
    },
    messages : {
      receiptId: {
        required: "This field is required",
        min: "ID is a positive number"
      }
    }
  });
});

$(document).ready(function() {
  $("#confirm-booking-form").validate({
    validClass: "valid success-handle",
    rules: {
      bookingId: {
        required: true,
        number: true,
        min: 1
      }
    },
    messages : {
      bookingId: {
        required: "This field is required",
        min: "ID is a positive number"
      }
    }
  });
});


$(document).ready(function() {
  $("#confirm-booking-room-form").validate({
    validClass: "valid success-handle",
    rules: {
      confirmRoomId: {
        required: true,
        number: true,
        min: 1
      }
    },
    messages : {
      confirmRoomId: {
        required: "This field is required",
        min: "ID is a positive number"
      }
    }
  });
});

$.validator.addMethod('typeRegex', function TypeRoomRegex(value,elem,args)
{
  if ( (value=='single') || (value=='standart') || (value=='suite')|| (value=='family') ) {
    return true;
  }
  return false;
}, 'Wrong room type');

$.validator.addMethod("greaterThan", 
function(value, element, params) {
  return this.optional(element) || new Date(value) > new Date($(params).val());
},'Must be greater than arrival date.');

$(document).ready(function() {
  $("#create-booking-form").validate({
    validClass: "valid success-handle",
    rules: {
      typeId: {
        required: true, 
        typeRegex: true,
      },
      guestsNum:
      {
        required: true, 
        number: true,
        min: 1
      },
      arrivalDate: 
      {
        required: true,
        date: true
      },
      departureDate: 
      {
        required: true,
        date: true,
        greaterThan: "#arrivalDate"
      }
    },
    messages : {
      typeId: {
        required: "This field is required",
        typeRegex: 'Only following types: single, standart, family, suite'
      },
      guestsNum: {
        required: "This field is required",
        min: "At least one guest"
      },
      arrivalDate: {
        required: "This field is required",
        date: "Wrong input format"
      },
      departureDate: {
        required: "This field is required",
        date: "Wrong input format", 
        greaterThan: "Should be greater than arrival date"
      }
    }
  });
});

$(document).ready(function() {
  $("#type-rooms-form").validate({
    validClass: "valid success-handle",
    rules: {
      typeIdRoom: {
        required: true, 
        typeRegex: true,
      },
      arrivalDateRoom:
      {
        required: true,
        date: true
      },
      departureDateRoom:
      {
        required: true,
        date: true,
        greaterThan: "#arrivalDateRoom"
      }
    },
    messages : {
      typeIdRoom: {
        required: "This field is required",
        typeRegex: 'Only following types: single, standart, family, suite'
      },
      arrivalDateRoom: {
        required: "This field is required",
        date: "Wrong input format"
      },
      departureDateRoom: {
        required: "This field is required",
        date: "Wrong input format", 
        greaterThan: "Should be greater than arrival date"
      }
    }
  });
});
