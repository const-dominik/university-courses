namespace Streams;

class IntStream
{
    int value;

    public IntStream()
    {
        value = 0;
    }

    public virtual int next()
    {
        if (this.eos())
            throw new OverflowException();
        return this.value++;
    }

    public virtual bool eos()
    {
        return (this.value == Int32.MaxValue);
    }

    public void reset()
    {
        this.value = 0;
    }
}