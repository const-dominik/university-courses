using Microsoft.AspNetCore.SignalR;

public class Startup
{
    public IConfiguration _configuration;
    public Startup(IConfiguration configuration)
    {
        _configuration = configuration;
    }


    public void ConfigureServices(IServiceCollection services)
    {
        services.AddCors(options =>
        {
            options.AddPolicy("AllowSpecificOrigin",
                builder =>
                {
                    builder.WithOrigins("http://localhost:3000")
                        .AllowAnyHeader()
                        .AllowAnyMethod()
                        .AllowCredentials();
                });
        });

        services.AddSignalR();

        MongoDBClient.Initialize(_configuration);
        var mongoDatabase = MongoDBClient.GetDatabase();
        services.AddSingleton(mongoDatabase);
        services.AddSingleton<TokenService>();
    }

    public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
    {

        if (env.IsDevelopment())
        {
            app.UseDeveloperExceptionPage();
        }

        app.UseDefaultFiles();
        app.UseStaticFiles();
        app.UseCors("AllowSpecificOrigin");

        app.UseRouting();

        app.UseEndpoints(endpoints =>
        {
            endpoints.MapHub<TicTacToeHub>("/tictactoe");
        });
    }
}