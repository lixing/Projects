package puzzle.game;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.IBinder;

public class BackgroundMusic extends Service
{
	private MediaPlayer	player;


	public IBinder onBind(Intent arg0)
	{
		return null;
	}

	public void onStart(Intent intent, int startId)
	{
		super.onStart(intent, startId);
		player = MediaPlayer.create(this, R.raw.backgroundmusic);
		player.setLooping(true);
		player.start();
	}

	public void onDestroy()
	{
		super.onDestroy();
		player.stop();
	}

}