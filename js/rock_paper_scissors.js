


var userChoice = prompt("Do you choose rock, paper or scissors?");

var makeCompChoice = function()
{
   var computerChoice = Math.random();
   if (computerChoice < 0.34)
   {
      computerChoice = "rock";
   }
   else if (computerChoice <= 0.67)
   {  
      computerChoice = "paper";
   }
   else
   {  
      computerChoice = "scissors";
   }
   console.log("Computer: " + computerChoice);
   return computerChoice;
}


var compare = function(choice1, choice2)
{

    if (choice1 === choice2)
    {
       choice1 = prompt("Do you choose rock, paper or scissors?");
        compare(choice1, makeCompChoice());
    }
    else if (choice1 === "rock")
    {
        if (choice2 === "scissors")
            return "rock wins";
        else
            return "paper wins";
    }
    else if (choice1 === "paper")
    {
        if (choice2 === "rock")
            return "paper wins";
        else
            return "scissors wins";
    }
    else if (choice1 === "scissors")
    {
        if (choice2 === "rock")
            return "rock wins";
        else
            return "scissors wins";
    }
   else {
      alert(choice1 + " is not a valid choice");

   }
}

compare(userChoice, makeCompChoice());
