#!/bin/sh

ejemplo=test-example-n4-clean.txt
instancia1=a280-n279-clean.txt
instancia2=a280-n1395-clean.txt
instancia3=a280-n2790-clean.txt
instancia4=fnl4461-n4460-clean.txt
instancia5=test-4461-n22300-clean.txt
instancia6=fnl4461-n44600-clean.txt
instancia7=pla33810-n33809-clean.txt
instancia8=pla33810-n169045-clean.txt
instancia9=pla33810-n338090-clean.txt
optEjemplo=test-example-n4-opt.txt
opt280=a280.opt.tour-clean.txt
opt280=a280.opt.tour_new.txt
opt4461=fnl4461.opt.tour-clean.txt
opt33810=pla33810.opt-clean.tour
planEjemplo=optPlan_4-3_clean.txt
plan1395=optPlan_280-1395_clean.txt
plan279=optPlan_280-279_clean.txt
plan2790=optPlan_280-2790_clean.txt
plan22300=optPlan_4461-22300_clean.txt
plan4460=optPlan_4461-4460_clean.txt
plan44600=optPlan_4461-44600_clean.txt
plan33809=optPlan_33810-33809_clean.txt
plan169045=optPlan_33810-169045_clean.txt
plan338090=optPlan_33810-338090_clean.txt


echo "instancia4: " $instancia4 $opt4461 $plan4460
echo "instancia5: " $instancia5 $opt4461 $plan22300
echo "instancia6: " $instancia6 $opt4461 $plan44600
echo "instancia7: " $instancia7 $opt33810 $plan33809
echo "instancia8: " $instancia8 $opt33810 $plan169045
echo "instancia9: " $instancia9 $opt33810 $plan338090

./ttp1_1 $ejemplo $optEjemplo $planEjemplo

#Comentario
