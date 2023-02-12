package com.itsallbinary.netty.chat;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

import io.netty.channel.Channel;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import java.util.logging.Logger;

/**
 * Handles a server-side channel.
 */
public class ChatServerHandler extends SimpleChannelInboundHandler<String> {

	
	

	// List of connected client channels.
	static final List<Channel> channels = new ArrayList<Channel>();

	private final static Random rowNumberRandomGenerator = new Random();
    private final static String fileWithRows = new String("D:/BSU/BSU/sem5/Web-programming/lab5_part3/lab/input.txt");
	private static ArrayList<String> rowsInFile = new ArrayList<String>();
	Logger logger = Logger.getLogger(ChatClient.class.getName());

	ChatServerHandler() {
		try {
			readRowsFromFile();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/*
	 * Whenever client connects to server through channel, add his channel to the
	 * list of channels.
	 */
	@Override
	public void channelActive(final ChannelHandlerContext ctx) {
		System.out.println("Client joined - " + ctx);
		channels.add(ctx.channel());
		logger.info("Client joined - " + ctx);
	}

	/*
	 * When a message is received from client, send that message to all channels.
	 * FOr the sake of simplicity, currently we will send received chat message to
	 * all clients instead of one specific client. This code has scope to improve to
	 * send message to specific client as per senders choice.
	 */
	@Override
	public void channelRead0(ChannelHandlerContext ctx, String msg) throws Exception {
		String serversAnswer = new String("\nServer's random row from file is - " + 
                                                                        rowsInFile.get(rowNumberRandomGenerator.nextInt(rowsInFile.size() - 1)));
		System.out.println("Server received - " + msg);
		for (Channel c : channels) {
			c.writeAndFlush("-> " + msg + '\n');
			c.writeAndFlush(serversAnswer);
		}
		logger.info(msg);
		logger.info(serversAnswer);
	}

	/*
	 * In case of exception, close channel. One may chose to custom handle exception
	 * & have alternative logical flows.
	 */
	@Override
	public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
		System.out.println("Closing connection for client - " + ctx);
		ctx.close();
	}

	private static void readRowsFromFile() throws FileNotFoundException 
    {
        File file = new File(fileWithRows);
        Scanner sc = new Scanner(file);
    
        while (sc.hasNextLine()) {
            rowsInFile.add(sc.nextLine());
        }

        sc.close();
    }
}
