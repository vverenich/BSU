find $3 -size +$1c -size -$2c -print |
while read fname 
do
   echo "$(dirname $fname)    $(basename $fname)"
done