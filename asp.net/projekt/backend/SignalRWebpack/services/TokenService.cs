using System;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using Microsoft.IdentityModel.Tokens;
using Microsoft.Extensions.Configuration;
using Coornick.Models;

public class TokenService
{
    private readonly IConfiguration _configuration;
    public Dictionary<string, string> jwts { get; private set; }

    public TokenService(IConfiguration configuration)
    {
        _configuration = configuration;
        jwts = new Dictionary<string, string>();
    }

    public void UpdateTokenOwner(string token, string socketId)
    {
        string keyToUpdate = string.Empty;

        foreach (var entry in jwts)
        {
            if (entry.Value.Equals(token))
            {
                keyToUpdate = entry.Key;
                break;
            }
        }

        if (keyToUpdate != string.Empty)
        {
            jwts.Remove(keyToUpdate);
            jwts[socketId] = token;
        }
        else
        {
            AddTokenToMap(socketId, token);
        }
    }

    public void AddTokenToMap(string socketId, string token)
    {
        DecodeToken(token);
        jwts[socketId] = token;
    }

    public string? GetTokenFromMap(string socketId)
    {
        jwts.TryGetValue(socketId, out var token);
        return token;
    }

    public string CreateToken(string socketId, string nick, string? email, DateTime? expiration = null)
    {
        string? jwtSecret = _configuration["JWT_SECRET"] ?? null;
        if (jwtSecret == null)
        {
            throw new System.Exception("JWT_SECRET not found");
        }

        var claims = new List<Claim>();

        if (!string.IsNullOrEmpty(nick))
        {
            claims.Add(new Claim("nick", nick));
        }

        if (!string.IsNullOrEmpty(email))
        {
            claims.Add(new Claim("email", email));
        }

        var key = new SymmetricSecurityKey(System.Text.Encoding.UTF8.GetBytes(jwtSecret));
        var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);

        var token = new JwtSecurityToken(
            issuer: "coornick",
            audience: "coornick",
            claims: claims,
            expires: expiration ?? DateTime.Now.AddDays(14),
            signingCredentials: creds);

        var writtenToken = new JwtSecurityTokenHandler().WriteToken(token);
        AddTokenToMap(socketId, writtenToken);
        return writtenToken;
    }
    public DecodedJWT? DecodeToken(string token)
    {
        string? jwtSecret = _configuration["JWT_SECRET"] ?? null;
        if (jwtSecret == null)
        {
            throw new System.Exception("JWT_SECRET not found");
        }

        var key = new SymmetricSecurityKey(System.Text.Encoding.UTF8.GetBytes(jwtSecret));
        var validationParameters = new TokenValidationParameters
        {
            ValidateIssuerSigningKey = true,
            IssuerSigningKey = key,
            ValidateIssuer = true,
            ValidIssuer = "coornick",
            ValidateAudience = true,
            ValidAudience = "coornick",
            ValidateLifetime = true,
            ClockSkew = TimeSpan.Zero
        };

        var handler = new JwtSecurityTokenHandler();
        SecurityToken validatedToken;
        try
        {
            handler.ValidateToken(token, validationParameters, out validatedToken);
        }
        catch (Exception)
        {
            return null;
        }

        var jwt = (JwtSecurityToken)validatedToken;
        var payload = jwt.Payload;

        return new DecodedJWT
        {
            Email = payload.TryGetValue("email", out var email) ? email.ToString() : null,
            Nick = payload.TryGetValue("nick", out var nick) ? nick.ToString() : "",
            Exp = payload.TryGetValue("exp", out var exp) ? Convert.ToInt64(exp) : 0
        };
    }
}