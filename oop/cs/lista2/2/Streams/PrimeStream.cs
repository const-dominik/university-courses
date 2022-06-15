namespace Streams;

class PrimeStream : IntStream {
    int value;
    public PrimeStream()
    {
        value = 1;            
    }

    bool isPrime(int n)
    {
        if (n <= 1) return false;
        if (n <= 3) return true;

        for (int i=2; i*i <= n; i++)
            if (n % i == 0)
                return false;
    
        return true;
    }

    override public int next()
    {
        if (base.eos()) return this.value;

        int oldValue = this.value;

        while (true)
        {
            this.value++;
            if (this.isPrime(this.value))
            {
                return this.value;
            }
            if (this.value == Int32.MaxValue)
            {
                base.isStreamEnded = true;
                this.value = oldValue;
                return this.value;
            }
        }
    }
}