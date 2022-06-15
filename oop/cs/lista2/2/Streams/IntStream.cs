namespace Streams;

class IntStream
{
    int value;
    protected bool isStreamEnded;

    public IntStream()
    {
        value = 0;
        isStreamEnded = false;
    }

    public virtual int next()
    {
        if (this.value == Int32.MaxValue)
        {
            this.isStreamEnded = true;
            return this.value;
        }
        return !this.eos() ? this.value++ : this.value;
    }

    public virtual bool eos()
    {
        return this.isStreamEnded;
    }

    public void reset()
    {
        this.value = 0;
        this.isStreamEnded = false;
    }
}