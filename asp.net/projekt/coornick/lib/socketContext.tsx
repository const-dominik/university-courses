import { createContext, ReactNode, useEffect, useState } from "react";
import * as signalR from "@microsoft/signalr";

export const HubConnectionsContext = createContext<signalR.HubConnection | null>(null);

interface IHubConnectionsProvider {
  children: ReactNode;
}

export const HubConnectionsProvider = ({ children }: IHubConnectionsProvider) => {
  const [socket, setSocket] = useState<signalR.HubConnection | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const createHubConnection = async (url: string) => {
      const connection = new signalR.HubConnectionBuilder()
        .withUrl(url)
        .withAutomaticReconnect()
        .build();

      try {
        await connection.start();
        console.log(`Connection to ${url} established successfully.`);
      } catch (err) {
        console.error(`Error while establishing connection to ${url} :(`, err);
      }

      return connection;
    };

    const initializeConnections = async () => {
      setSocket(await createHubConnection("http://localhost:5253/tictactoe"));
      setLoading(false);
    };

    initializeConnections();
  }, []);

  if (loading) {
    return <div>Loading...</div>;
  }

  return (
    <HubConnectionsContext.Provider value={ socket }>
      {children}
    </HubConnectionsContext.Provider>
  );
};