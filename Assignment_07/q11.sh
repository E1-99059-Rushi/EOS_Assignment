

#!/bin/bash

echo "Enter salary: "
read salary

deduction=$((salary * 20 / 100 + salary * 40 / 100))
grossSal=$((salary - deduction))

echo "Deduction: $deduction"
echo "Gross Salary: $grossSal"   




