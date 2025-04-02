import '../styles/globals.css'
import type { AppProps } from 'next/app'
import { useEffect, useState } from 'react';
import Cookies from 'js-cookie';
import { AuthContext } from '../lib/authContext';
import { HubConnectionsProvider } from '../lib/socketContext';
import { useSocket } from '../hooks/useSocket';

export default function App({ Component, pageProps }: AppProps) {
  const [isAuthorized, setIsAuthorized] = useState<boolean | null>(null);
  const socket = useSocket();

  useEffect(() => {
    if (socket) {
      socket.on("isTokenOk", (isOk) => {
        setIsAuthorized(isOk);
      });

      const token = Cookies.get("token");
      if (!token) {
        setIsAuthorized(false);
        return;
      }
      socket.invoke("CheckTokenValidity", token);
    }
  }, [socket])
  
  return (
    <HubConnectionsProvider>
      <AuthContext.Provider value={{
        isAuthorized,
        setIsAuthorized
      }}>
          <Component {...pageProps} />
      </AuthContext.Provider>
    </HubConnectionsProvider>
  )
}