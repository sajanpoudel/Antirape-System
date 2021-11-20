# Registered numbers

The numbers that receive the rescue message are the `contacts` array at the top of `Antirape-watch.ino`. Use the international format, for example `+97798XXXXXXXX`. Change `CONTACT_COUNT` when you add or remove numbers.

The call placed by `sendcall()` goes to the last entry of the array.
