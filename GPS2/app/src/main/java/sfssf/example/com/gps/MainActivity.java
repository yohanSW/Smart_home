package sfssf.example.com.gps;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

/** GPS ���� */
public class MainActivity extends Activity {

    private Button btnShowLocation;
    private TextView txtLat;
    private TextView txtLon;

    // GPSTracker class
    private GpsInfo gps;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnShowLocation = (Button) findViewById(R.id.button);
        txtLat = (TextView) findViewById(R.id.Latitude);
        txtLon = (TextView) findViewById(R.id.Longitude);
        Intent GPSt = new Intent(this, GpsInfo.class);
        startService(GPSt);

        // GPS ������ �����ֱ� ���� �̺�Ʈ Ŭ���� ���
        btnShowLocation.setOnClickListener(new View.OnClickListener() {

            public void onClick(View arg0) {
                gps = new GpsInfo(MainActivity.this);
                // GPS ������� ��������

                if (gps.isGetLocation()) {

                    double latitude = gps.getLatitude();
                    double longitude = gps.getLongitude();

                    txtLat.setText(String.valueOf(latitude));
                    txtLon.setText(String.valueOf(longitude));

                    Toast.makeText(
                            getApplicationContext(),
                            "����� ��ġ - \n����: " + latitude + "\n�浵: " + longitude,
                            Toast.LENGTH_LONG).show();
                } else {
                    // GPS �� ����Ҽ� �����Ƿ�
                    gps.showSettingsAlert();
                }
            }
        });
    }
}
