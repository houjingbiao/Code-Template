// calculate e
int digits[1000], i, d, carry;
int main() {
	for(i = 1; i < 1000; i++) digits[i] = 1;
	digits[1] = 2;
	while(1) {
		putchar(digits[1] + '0');
		digits[1] = 0; carry = 0;
		for(i = 999; i > 1; i--){
			d = digits[i]*10+carry;
			digits[i] = d%i;
			carry = d/i;
		}
		digits[1] = carry;
	}
}