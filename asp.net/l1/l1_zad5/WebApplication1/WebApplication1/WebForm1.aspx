<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="WebApplication1.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <asp:Label runat="server">Wpisz imię:</asp:Label>
        <asp:TextBox ID="userName" runat="server" />
        <asp:Button ID="btnSubmit" runat="server" Text="Prześlij" OnClick="onSubmit" />
    </form>
</body>
</html>
