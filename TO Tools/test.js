var v1, v2, r1, last_calculated, calculate_now, last_calculated2, calculate_now2;
function validate(field_req, form_name) {
  var num1, count = 0;
  num1 = Number(document.forms[form_name]["resistor2"].value);

  document.getElementById(form_name + "_R2_value").innerHTML = "R2 = " + num1 + display_unit(form_name, "R2_unit");
  if (check_not_empty(num1))//&& last_calculated != 1) 
  {
    count++;
    v1 = true;
  }
  else {
    v1 = false;
    // last_calculated = 1;
  }
  num1 = Number(document.forms[form_name]["resistor1"].value);
  document.getElementById(form_name + "_R1_value").innerHTML = "R1 = " + num1 + display_unit(form_name, "R1_unit");
  if (check_not_empty(num1))// && last_calculated != 2)
  {
    count++;
    v2 = true;
  }
  else {
    v2 = false;
    // last_calculated = 2;
  }
  num1 = Number(document.forms[form_name]["result"].value);
  document.getElementById(form_name + "_G_value").innerHTML = "G  = " + num1;
  if (check_not_empty(num1))//&& last_calculated != 3)
  {
    count++;
    r1 = true;
    if (form_name === "amplifier2" && num1 >= 0) {

      document.forms[form_name]["result"].value = -num1;
    }
  }
  else {
    r1 = false;
    // last_calculated = 3;
  }
  console.log(count);

  if (count >= field_req) {
    document.forms[form_name]["calculate"].disabled = false;
    if (!v1) {
      console.log("R2 calculate");
      if (form_name === "amplifier1") {
        calculate_now = 1;
        last_calculated = 1;
      }
      else if (form_name === "amplifier2") {
        calculate_now2 = 1;
        last_calculated2 = 1;
      }
      document.getElementById(form_name + "_R2_input").className = "com input-R output_field";
      document.getElementById(form_name + "_R1_input").className = "com input-R";
      document.getElementById(form_name + "_result").className = "com input-R";
    }
    else if (!v2) {
      console.log("R1 calculate");
      if (form_name === "amplifier1") {
        calculate_now = 2;
        last_calculated = 2;
      }
      else if (form_name === "amplifier2") {
        calculate_now2 = 2;
        last_calculated2 = 2;
      }
      document.getElementById(form_name + "_R1_input").className = "com input-R output_field";
      document.getElementById(form_name + "_R2_input").className = "com input-R";
      document.getElementById(form_name + "_result").className = "com input-R";
    }
    else if (!r1) {
      console.log("result calculate");
      if (form_name === "amplifier1") {
        calculate_now = 3;
        last_calculated = 3;
      }
      else if (form_name === "amplifier2") {
        calculate_now2 = 3;
        last_calculated2 = 3;
      }
      document.getElementById(form_name + "_result").className = "com input-R output_field";
      document.getElementById(form_name + "_R1_input").className = "com input-R";
      document.getElementById(form_name + "_R2_input").className = "com input-R";
    }
    else {
      console.log("calculate last value");
      if (form_name === "amplifier1") {
        calculate_now = last_calculated;
      }
      else if (form_name === "amplifier2") {
        calculate_now2 = last_calculated2;
      }
    }
  }
  else {
    document.forms[form_name]["calculate"].disabled = true;
  }
}

function check_not_empty(val1) {
  if (val1 == null || val1 == "") {
    return false;
  }
  else {
    return true;
  }
}

// this function used to display the resistor unit selected in the div tag
function display_unit(form_name, name_selected) {
  var unit_selected = Number(document.forms[form_name][name_selected].value);
  if (unit_selected === 1) {
    return " Ω";
  }
  else if (unit_selected === 1000) {
    return " KΩ";
  }
  else {
    return " MΩ";
  }
}
function unit_selected(val1, val2) {
  if (val2 === "kilo") {
    console.log("kilo selected");
    val1 = val1 * 1000;
  }
  else if (val2 === "mega") {
    console.log("mega selected");
    val1 = val1 * 1000000;
  }
  return val1;
}


function calculateGain(form_name) {
  console.log("calculating");
  var num1, num2, unit1, unit2;
  /*forms[form_name]["resistor2"].value*/
  unit1 = Number(document.forms[form_name]["R2_unit"].value);  // reading the unit selected for resistor 2
  unit2 = Number(document.forms[form_name]["R1_unit"].value);  // reading the unit selected for resistor 1
  num1 = Number(document.forms[form_name]["resistor2"].value) * unit1;
  num2 = Number(document.forms[form_name]["resistor1"].value) * unit2;
  res = Number(document.forms[form_name]["result"].value);

  if (form_name === "amplifier1") {

    if (calculate_now == 3 || (v1 && v2 && !r1)) {
      res = 1 + (num1 / num2);
      console.log(res);
      res = Math.round((res + Number.EPSILON) * 100) / 100;
      document.forms[form_name]["result"].value = res;
      last_calculated = 3;
      document.getElementById(form_name + "_G_value").innerHTML = "G  = " + res;  // showing gain value
    }

    else if (calculate_now == 2 || (v1 && !v2 && r1)) {
      num2 = (num1 / (res - 1)) / unit2;
      console.log(num2);
      num2 = Math.round((num2 + Number.EPSILON) * 100) / 100;
      document.forms[form_name]["resistor1"].value = num2;
      last_calculated = 2;
      document.getElementById(form_name + "_R1_value").innerHTML = "R1 = " + num2 + display_unit(form_name, "R1_unit");
    }

    else {
      num1 = (num2 * (res - 1)) / unit1;
      console.log(num1);
      num1 = Math.round((num1 + Number.EPSILON) * 100) / 100;
      document.forms[form_name]["resistor2"].value = num1;
      last_calculated = 1;
      document.getElementById(form_name + "_R2_value").innerHTML = "R2 = " + num1 + display_unit(form_name, "R2_unit");
    }
  }

  else if (form_name === "amplifier2") {

    if (calculate_now2 == 3 || (v1 && v2 && !r1)) {
      res = -(num1 / num2);
      console.log(res);
      res = Math.round((res + Number.EPSILON) * 100) / 100;
      document.forms[form_name]["result"].value = res;
      last_calculated2 = 3;
      document.getElementById(form_name + "_G_value").innerHTML = "G  = " + res;  // showing gain value
    }

    else if (calculate_now2 == 2 || (v1 && !v2 && r1)) {
      num2 = (num1 / (-res)) / unit2;
      console.log(num2);
      num2 = Math.round((num2 + Number.EPSILON) * 100) / 100;
      document.forms[form_name]["resistor1"].value = num2;
      last_calculated2 = 2;
      document.getElementById(form_name + "_R1_value").innerHTML = "R1 = " + num2 + display_unit(form_name, "R1_unit");
    }

    else {
      num1 = (num2 * (-res)) / unit1;
      console.log(num1);
      num1 = Math.round((num1 + Number.EPSILON) * 100) / 100;
      document.forms[form_name]["resistor2"].value = num1;
      last_calculated2 = 1;
      document.getElementById(form_name + "_R2_value").innerHTML = "R2 = " + num1 + display_unit(form_name, "R2_unit");
    }
  }

}

function clear_all(form_name) 
{
  console.log("clear all from "+form_name );
  document.forms[form_name]["resistor2"].value = ""; // clear all 3 input fields
  document.forms[form_name]["resistor1"].value = "";
  document.forms[form_name]["result"].value = "";
  document.forms[form_name]["R2_unit"].value = 1;
  document.forms[form_name]["R1_unit"].value = 1;
  document.forms[form_name]["calculate"].disabled = true; //disable calculate button
  // all CSS back to normal
  if (form_name === "amplifier1") {
    if (last_calculated === 1) {
      document.getElementById(form_name + "_R2_input").className = "com input-R";
    }
    else if (last_calculated === 2) {
      document.getElementById(form_name + "_R1_input").className = "com input-R";
    }
    else if (last_calculated === 3) {
      document.getElementById(form_name + "_result").className = "com input-R";
    }
  }
  else if (form_name === "amplifier2") {
    if (last_calculated2 === 1) {
      document.getElementById(form_name + "_R2_input").className = "com input-R";
    }
    else if (last_calculated2 === 2) {
      document.getElementById(form_name + "_R1_input").className = "com input-R";
    }
    else if (last_calculated2 === 3) {
      document.getElementById(form_name + "_result").className = "com input-R";
    }
  }
}

/* this function will only allow to enter numeric value in the input field*/
function isNumberKey(evt) {
  var charCode = (evt.which) ? evt.which : evt.keyCode
  // if (charCode > 31 && (charCode < 48 || charCode > 57))  // for non decimal numbers
  if (charCode > 31 && (charCode != 46 && (charCode < 48 || charCode > 57)))   // for decimal place numbers
    return false;
  return true;
}

/* Reference
For seting the input for just numbers
https://stackoverflow.com/a/13952727/11597205

*/