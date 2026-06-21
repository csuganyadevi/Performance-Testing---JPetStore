void generate_random_15_digit()
{
    char card[20] = "";
    int i;

    srand(time(NULL));

    for (i = 0; i < 15; i++)
    {
        char digit[2];
        sprintf(digit, "%d", rand() % 10);
        strcat(card, digit);
    }

    lr_param_sprintf("CreditCard", "%s", card);

    lr_output_message("Generated Card: %s", lr_eval_string("{CreditCard}"));
}