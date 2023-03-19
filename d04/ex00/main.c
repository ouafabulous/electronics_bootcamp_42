void    i2c_init(void)
{
    TWBR = (CPU_CL_F / (2 *(SCL_F * PRESCALER))) - 8;
}

void    i2c_start(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void    i2c_stop(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
